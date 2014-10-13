
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

/**
 * Read the fix value in a string and convert to the proper type (if need be)<br>
 * Sample Code for int32_t:<br>
 * std::string strFieldName = nos.getField(FIX::FIELD::FieldName);
 */
void Functions::copyFrom(const string &fixFieldName, const Field &field, stringstream &sourceCode) {
	string strFIXValueVarName = getFIXValue( fixFieldName, field, sourceCode);

	encode( strFIXValueVarName, fixFieldName, field, sourceCode);
}

/**
 * Encode a string value into the appropriate output format (based on field type)<br>
 * Sample Code for int32_t<br>
 * int32_t iValue = std::atoi( strFixValue);
 * Codec::encode( iValue, pos);
 * Sample code for string<br>
 * Codec::encode( strVar, pos, size);
 */
void Functions::encode( const string&strVarName, const string &fixFieldName, const Field& field, stringstream& sourceCode) {

	string typeName;
	switch (field.type) {
	case STRING:
		sourceCode << "\tCodec::encode(" << strVarName << ", msg, " << field.position << ", " << field.size << ");" << endl;
		break;
	case INT8:
	case INT16:
	case INT32:
	case UINT8:
	case UINT16:
	case UINT32:
	case INT64:
	case UINT64: {
		string intVarName = "i" + fixFieldName;
		typeName = Field::getTypeName(field.type);
		sourceCode << "\t" << typeName << " " << intVarName << " = ";
		if (field.type == INT64 || field.type == UINT64) {
			sourceCode << "std::stol(";
		}
		else {
			sourceCode << "std::stoi(";
		}
		sourceCode << strVarName << ")" << endl;
		sourceCode << "\tCodec::encode(" << intVarName << ", msg, " << field.position << ");" << endl;
	}	break;
	default:
		sourceCode << "\t// TODO This data type is not implemented " << Field::getTypeName(field.type);
	}

}

/**
 * The objective is to read the FIX representation in a string and invoke the Mapper on this 
 * Sample code:
 * std::string strFieldName = nos.getField( FIX::FIELD::FieldName);
 * std::string mappedValue = mapper.sideFrom( strFieldName);
 * Codec::encode( mappedValue, pos, size);
 */
void Functions::mappingFrom(const MappingTable &mappingTable, const string &fixFieldName, const Field &field, stringstream &sourceCode) {
	string strFIXValueVarName = getFIXValue( fixFieldName, field, sourceCode);
	string strMappedValueVarName = getMappedValue( mappingTable, strFIXValueVarName, field, sourceCode);
	encode(strMappedValueVarName, fixFieldName, field, sourceCode);
}


string Functions::getFIXValue( const string &fixFieldName, const Field &field, stringstream &sourceCode) {
	string strOutput = "str" + fixFieldName;

	// Print a short header
	sourceCode << endl << "\t// " << fixFieldName << " " << Field::getTypeName(field.type) << " @" << field.position << "," << field.size << endl;
	// get field value as string
	sourceCode << "\tstd::string " << strOutput << " = nos.getField(FIX::FIELD::" << fixFieldName << ");" << endl;

	return strOutput;
}

FunctionType Functions::getFunctionType(std::string value) {
	if (!value.compare(0, 9, "copyFrom(")) return COPY_FROM;
	if (!value.compare(0, 12, "mappingFrom(")) return MAPPING_FROM;
	return UNKNOWN;
}

/**
 * Source Code sample:<br>
 * int8_t mappedValue = mapper.sideFrom( strFIXValueVarName);
 */
string Functions::getMappedValue( const MappingTable &mappingTable, const string &strVarName, const Field &field, stringstream &sourceCode) {
	string strOutputVarName = "native_" + strVarName;

	sourceCode << "\t" << Field::getTypeName(field.type) << " " << strOutputVarName << " = mapper." << mappingTable.name << "From.find(" << strVarName << ");" << endl;

	return strOutputVarName;
}

string & Functions::getParameter(const string &value, int index, string &output) {
	string::size_type start_position;
	string::size_type end_position = 0;
	while (index-- > 0) {
		start_position = value.find("\'", ++end_position);
		end_position = value.find("\'", ++start_position);
	}

	output = value.substr(start_position, (end_position - start_position));

	return output;
}


}
