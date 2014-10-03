#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <ctype.h>

#include <json/json.h>

using namespace std;

void patternReplace( const string& pattern, const string& value, string &source);
string getFunctionParameter( const string &, int pos);
void codeGetFieldValue( const string &fixFieldName, stringstream &sourceCode);

int main( int argc, char *argv[]) {
    string directory;
    string nameSpace;
    if( argc != 3) {
        cerr << "Usage: " << argv[0] << " {AdapterDirectory} {namespace}" << endl;
        exit(1);
    } else {
        directory = argv[1];
        nameSpace = argv[2];
    }
    cout << "Using : directory=" << directory << ", namespace=" << nameSpace << endl;

    // Load source file into adapterSource
    string adapterFilename = "templates/__namespace__Adapter.cpp";
    ifstream t(adapterFilename.c_str());
    string adapterSource((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

    std::time_t now = std::time(NULL);
    char today[100];
    strftime( today, (unsigned long)sizeof(today), "%F", std::localtime(&now));

    // replace __namespace__ with second parameter
    patternReplace( "__namespace__", nameSpace, adapterSource);
    patternReplace( "__date__", today, adapterSource);

    cout << adapterSource << endl;

    // read description
    Json::Value root;
    Json::Reader reader;

    string descriptionFilename = directory + "description.json";
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
    cout << "I see " << messages.size() << " message(s)." << endl;

    string fixNewOrderSingle( "NewOrderSingle");

    for( unsigned int index = 0; index < messages.size(); ++index) {
        const Json::Value message = messages[index];
        const Json::Value fields = message["fields"];
        const Json::Value fixMessage = message["fixMessage"];

        // cout << "Message " << message["name"] << " as " << fields.size() << " fields" << endl;
        if( fixMessage.isNull()) continue;
        if( fixNewOrderSingle.compare( fixMessage.asString())) {
			stringstream nosEncoding;
			for( int indexField = 0; indexField < (int)fields.size(); ++indexField) {
				Json::Value field = fields[ indexField];
				Json::Value value = field["value"];
				if( value.isNull()) {
					cout << "Field " << field["name"] << " has no value" << endl;
					continue;
				}

				if( strncmp( value.asCString(), "copyFrom(", 9) == 0) {
					string fixFieldName = getFunctionParameter( value, 1);
					codeGetFieldValue( fixFieldName, nosEncoding);
				}
			}
        }
    }
}


void patternReplace( const string& pattern, const string& value, string &source) {
    ::size_t pos = 0;
    ::size_t len = pattern.length();
    while( ( pos = source.find( pattern, pos)) != string::npos) {
        source.replace( pos, len, value);
    }
}

void codeGetFieldValue( const string &fixFieldName, stringstream &sourceCode) {
	string varName = fixFieldName;
	varName[0] = tolower( varName[0]);

	sourceCode << "\tstd::string " << varName << " = nos.getField(FIX::FIELD::" << fixFieldName << ")" << endl;
}

string getFunctionParameter( const string &value, int index, string &output) {
	string::size_type start_position;
	string::size_type end_position = 0;
	while( index > 0) {
		start_position = value.find( "\'", ++end_position);
		end_position = value.find( "\'", ++start_position);
	}
}
