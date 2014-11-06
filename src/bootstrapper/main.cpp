#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <ctype.h>
#include <stdexcept>

#include <json/json.h>

#include "Functions.h"
#include "Field.h"
#include "MappingTable.h"

using namespace std;
using namespace Bootstrapper;

#define VERSION "Bootstrapper v0.1"

void patternReplace( const string& pattern, const string& value, string &source);
MappingTable * getMappingTableByName(vector<MappingTable*>mappingTables, string mappingTableName);
string & loadFile(const string &templateDir, const string &fileName, string &sourceString);
void writeFile(const string& adapterDir, const string & fileName, const string& content);

/**
 * Main source 
 */
int main( int argc, char *argv[]) {
	// Figure out directories
    string adapterDir;
    string templateDir;
    if( argc != 3) {
        cerr << "Usage: " << argv[0] << " {AdapterDirectory} {TemplateDirectory}" << endl;
        exit(1);
    } else {
		adapterDir = argv[1];
        templateDir = argv[2];
    }
	cout << "Adapter Directory = " << adapterDir << endl;
	cout << "Template Directory = " << templateDir << endl;

    // Load template files into strings
	string adapterSource;
	loadFile(templateDir, "Adapter.cpp", adapterSource);
	string mapperSource;
	loadFile(templateDir, "Mapper.cpp", mapperSource);
	string mapperHeader;
	loadFile(templateDir, "Mapper.h", mapperHeader);

	// Format today's date
    std::time_t now = std::time(NULL);
    char todayValue[100];
    strftime( todayValue, (unsigned long)sizeof(todayValue), "%Y-%m-%d", std::localtime(&now));

    // read description.json
    Json::Value root;
    Json::Reader reader;

    string descriptionFilename = adapterDir + "/description.json";
    std::ifstream t2(descriptionFilename.c_str());
    std::string descriptionSource((std::istreambuf_iterator<char>(t2)),
            std::istreambuf_iterator<char>());
    cout << "Parsing " << descriptionFilename << endl;
    bool parsingSuccessful = reader.parse( descriptionSource, root);
    if( !parsingSuccessful) {
        cout << "Parsing failed : " << reader.getFormattedErrorMessages();
        exit(1);
    }
    cout << "Parsing successful" << endl;

	// are there properties?
	const Json::Value properties = root["properties"];
	if (properties.isNull()) {
		cout << "\"properties\" are missing from description" << endl;
		exit(1);
	}
	if (properties["namespace"].isNull()) {
		cout << "\"namespace\" is missing from \"properties\"" << endl;
	}
	string namespaceValue;
	namespaceValue = properties["namespace"].asString();

	// Are there messages?
	const Json::Value messages = root["messages"];
	if (messages.isNull()) {
		cout << "Messages are missing from description" << endl;
		exit(1);
	}
	cout << "I see " << messages.size() << " message(s)." << endl;

	// Are there mapping tables?
	const Json::Value mappings = root["mappingTables"];
	vector<MappingTable*> mappingTables;
	stringstream mappingTablesDeclarations;
	stringstream mappingTablesInitializations;

	if (!mappings.isNull()) {
		mappingTables.reserve(mappings.size());
		for (unsigned int index = 0; index < mappings.size(); ++index) {
			Json::Value mapping = mappings[index];
			MappingTable *newMT = new MappingTable(mapping);
			mappingTables.push_back( newMT);
			newMT->addDeclaration( mappingTablesDeclarations);
			newMT->addInitialization( mappingTablesInitializations);
		}
	}



	string fixNewOrderSingle("NewOrderSingle");

	stringstream nosEncoding;
	for (unsigned int index = 0; index < messages.size(); ++index) {
        const Json::Value message = messages[index];
        const Json::Value fields = message["fields"];
        const Json::Value fixMessage = message["fixMessage"];

        cout << "Message " << message["name"].asString() << " has " << fields.size() << " fields. fixMessage=" << fixMessage.asString() << endl;
        if( fixMessage.isNull()) continue;
        if( fixNewOrderSingle.compare( fixMessage.asString()) == 0) {
			// browse fields
			for( int indexField = 0; indexField < (int)fields.size(); ++indexField) {
				try {
					Json::Value jsonField = fields[ indexField];
					Field normalizedField(jsonField);
					Json::Value value = jsonField["value"];
					if( value.isNull()) {
						cout << "Field " << jsonField["name"] << " has no value" << endl;
						continue;
					}
					string strValue = value.asString();
					cout << "Field " << jsonField["name"] << " value=" << strValue << endl;

					switch (Functions::getFunctionType(strValue)) {
					case COPY_FROM: {
						string fixFieldName;
						Functions::getParameter(value.asString(), 1, fixFieldName);
						//cout << "fix field name=" << fixFieldName << endl;
						Functions::copyFrom(fixFieldName, normalizedField, nosEncoding);

					} break;
					case MAPPING_FROM: {
						string mappingTableName;
						string fixFieldName;
						Functions::getParameter(strValue, 1, mappingTableName);
						Functions::getParameter(strValue, 2, fixFieldName);
						MappingTable *mappingTable = getMappingTableByName(mappingTables, mappingTableName);
						if (mappingTable == NULL) throw std::runtime_error("Unknown Mapping Table " + mappingTableName + " referenced by field " + strValue);
						Functions::mappingFrom( *mappingTable, fixFieldName, normalizedField, nosEncoding);
					}	break;
					case UNKNOWN:
						throw std::runtime_error("unknonwn function type for " + strValue);
					}
				} catch (exception &e) {
					cerr << "Could not process field at position " << indexField << " because " << e.what() << endl;
				}
			}
        }
    }

	// replace patterns in adapter
	patternReplace("__namespace__", namespaceValue, adapterSource);
	patternReplace("__date__", todayValue, adapterSource);
	patternReplace("__nos-encoding__", nosEncoding.str(), adapterSource);
	patternReplace("__author__", VERSION, adapterSource);
	writeFile(adapterDir, "Adapter.cpp", adapterSource);


	// replace patterns for mapper
	patternReplace("__namespace__", namespaceValue, mapperSource);
	patternReplace("__mapping_tables_initialization__", mappingTablesInitializations.str(), mapperSource);
	writeFile(adapterDir, "Mapper.cpp", mapperSource);

	// replace patterns for mapper header
	patternReplace("__namespace__", namespaceValue, mapperHeader);
	patternReplace("__mapping_tables_declaration__", mappingTablesDeclarations.str(), mapperHeader);
	writeFile(adapterDir, "Mapper.h", mapperHeader);

//	cout << adapterSource << endl;
	cout << mapperSource << endl;
//	cout << mapperHeader << endl;
	cout << "Done";
}

/**
 * Locate a specific mapping table in the list of existing tables
 * @param mappingTables list of all known mapping tables
 * @param mappingTableName Name of the table we are looing for
 * @return whatever has been found or NULL if this table does not exist
 */
MappingTable * getMappingTableByName(vector<MappingTable*>mappingTables, string mappingTableName) {
	for (vector<MappingTable*>::iterator iter = mappingTables.begin(); iter != mappingTables.end(); ++iter) {
		MappingTable *pMT = *iter;
		if (!mappingTableName.compare(pMT->name)) return pMT;
	}
	return NULL;
}

/**
 * Loads file content into a string
 */
string & loadFile( const string &templateDir, const string &fileName, string &sourceString) {
	string fullFileName = templateDir + "/" + fileName;
	ifstream t(fullFileName.c_str());
	if (t.rdstate() & std::ifstream::failbit) {
		cerr << "Could not open template file " << fullFileName << endl;
		exit(1);
	}
	sourceString = string((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	return sourceString;
}

void patternReplace( const string& pattern, const string& value, string &source) {
    ::size_t pos = 0;
    ::size_t len = pattern.length();
    while( ( pos = source.find( pattern, pos)) != string::npos) {
        source.replace( pos, len, value);
    }
}

void writeFile( const string& directory, const string &fileName, const string & content) {
	ofstream out(directory + "/" + fileName);
	out << content;
	out.close();
}
