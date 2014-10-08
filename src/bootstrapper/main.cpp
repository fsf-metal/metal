#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <ctype.h>

#include <json/json.h>

#include "Functions.h"
#include "Field.h"

using namespace std;
using namespace Bootstrapper;

void patternReplace( const string& pattern, const string& value, string &source);
string & getFunctionParameter( const string &, int pos, string &output);

int main( int argc, char *argv[]) {
    string adapterDir;
    string templateDir;
    if( argc != 3) {
        cerr << "Usage: " << argv[0] << " {AdapterDirectory} {TemplateDirectory}" << endl;
        exit(1);
    } else {
		adapterDir = argv[1];
        templateDir = argv[2];
    }
	cout << "Using : adapter=" << adapterDir << ", template=" << templateDir << endl;

    // Load source file into adapterSource
    string adapterFilename = templateDir + "/__namespace__Adapter.cpp";
    ifstream t(adapterFilename.c_str());
    string adapterSource((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	// Format today's date
    std::time_t now = std::time(NULL);
    char todayValue[100];
    strftime( todayValue, (unsigned long)sizeof(todayValue), "%Y-%m-%d", std::localtime(&now));

    // read description
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

    const Json::Value messages = root["messages"];
	if (messages.isNull()) {
		cout << "Messages are missing from description" << endl;
		exit(1);
	}
    cout << "I see " << messages.size() << " message(s)." << endl;

	string namespaceValue;
	const Json::Value properties = root["properties"];
	if (properties.isNull()) {
		cout << "\"properties\" are missing from description" << endl;
		exit(1);
	}
	if (properties["namespace"].isNull()) {
		cout << "\"namespace\" is missing from \"properties\"" << endl;
	}
	namespaceValue = properties["namespace"].asString();

    string fixNewOrderSingle( "NewOrderSingle");

	stringstream nosEncoding;
	for (unsigned int index = 0; index < messages.size(); ++index) {
        const Json::Value message = messages[index];
        const Json::Value fields = message["fields"];
        const Json::Value fixMessage = message["fixMessage"];

        cout << "Message " << message["name"].asString() << " has " << fields.size() << " fields. fixMessage=" << fixMessage.asString() << endl;
        if( fixMessage.isNull()) continue;
        if( fixNewOrderSingle.compare( fixMessage.asString()) == 0) {
			for( int indexField = 0; indexField < (int)fields.size(); ++indexField) {
				try {

					Json::Value jsonField = fields[ indexField];
					Field normalizedField(jsonField);
					Json::Value value = jsonField["value"];
					if( value.isNull()) {
						cout << "Field " << jsonField["name"] << " has no value" << endl;
						continue;
					}
					cout << "Field " << jsonField["name"] << " value=" << value.asString() << endl;

					if( strncmp( value.asCString(), "copyFrom(", 9) == 0) {
						cout << "copyFrom() found" << endl;
						string fixFieldName;
						getFunctionParameter(value.asString(), 1, fixFieldName);
						cout << "fix field name=" << fixFieldName << endl;
						Functions::copyFrom( fixFieldName, normalizedField, nosEncoding);
					}
				} catch (exception &e) {
					cerr << "Could not process field at position " << indexField << " because " << e.what() << endl;
				}
			}
        }
    }

	// replace patterns with second parameter
	patternReplace("__namespace__", namespaceValue, adapterSource);
	patternReplace("__date__", todayValue, adapterSource);
	patternReplace("__nos-encoding__", nosEncoding.str(), adapterSource);

	cout << adapterSource << endl;

}


void patternReplace( const string& pattern, const string& value, string &source) {
    ::size_t pos = 0;
    ::size_t len = pattern.length();
    while( ( pos = source.find( pattern, pos)) != string::npos) {
        source.replace( pos, len, value);
    }
}

string & getFunctionParameter( const string &value, int index, string &output) {
	string::size_type start_position;
	string::size_type end_position = 0;
	while( index-- > 0) {
		start_position = value.find( "\'", ++end_position);
		end_position = value.find( "\'", ++start_position);
	}

	output = value.substr(start_position, (end_position - start_position));

	return output;
}
