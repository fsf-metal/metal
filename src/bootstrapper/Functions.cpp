
#include <string>
#include <sstream>

#include "Functions.h"

using namespace std;

namespace Bootstrapper {

Functions::Functions()
{
}


Functions::~Functions()
{
}

void Functions::copyFrom(const string &fixFieldName, const Field &field, stringstream &sourceCode) {
	string strVarName = "str" + fixFieldName;
//	strVarName[0] = tolower(strVarName[0]);
	string intVarName = "i" + fixFieldName;

	// get field value as string
	sourceCode << "\tstd::string " << strVarName << " = nos.getField(FIX::FIELD::" << fixFieldName << ");" << endl;

	// store it
	int position = field.position;
	switch (field.type) {
	case STRING:
		sourceCode << "\tCodec::encode(" << strVarName << ", msg, " << position << ", " << field.size << ");" << endl;
		break;
	case INT8:
		string typeName;
		sourceCode << "\t" << typeName << " " << intVarName << ", msg, " << position << ");" << endl;
		sourceCode << "\tCodec::encode(" << varName << ", msg, " << position << ", " << field.size << ");" << endl;

	}
	if (field.type == FieldType::STRING) {
	} else {
		cout << " Field " << field.name << " type is not processed" << endl;
	}
}

}
