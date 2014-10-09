#ifndef __METAL_FUNCTIONS_H
#define __METAL_FUNCTIONS_H

#include <string>
#include <iostream>

#include <json/json.h>

#include "Field.h"

enum FunctionType { COPY_FROM, MAPPING_FROM, UNKNOWN };

using namespace std;

namespace Bootstrapper {

	class Functions
	{
	public:
		Functions();
		~Functions();

		static void copyFrom(const string &fixFieldName, const Field &field, stringstream &sourceCode);
		static void mappingFrom(const string &tableName, const string &fixFieldName, const Field &field, stringstream &sourceCode);

		/**
		* Find out the function type from it's text representation
		* @param text something like "copyFrom('Account')"
		* @return the corresponding function type or FunctionType.UNKNOWN
		*/
		static FunctionType getFunctionType(std::string value);

		/**
		* @param value string containing the function call
		* @param index 1 based parameter index
		* @param output where the result will go (besides return value)
		*/
		static string & getParameter(const string &value, int index, string &output);

	protected:
		static void encode(const string&strVarName, const string &fixFieldName, const Field& field, stringstream& sourceCode);
		static string getFIXValue(const string &fixFieldName, const Field &field, stringstream &sourceCode);

		/**
		* Produces the code to map a FIX value into native
		* @param tableName name of the mapping table.
		* @param strVarName variable holding the string representation of the FIX value
		* @param field the native field representation
		* @param sourceCode where code should be generated
		* @return the variable that is storing the output. Could be of any type.
		*/
		static string getMappedValue(const string &tableName, const string &strVarName, const Field &field, stringstream &sourceCode);


	};

}

#endif // __METAL_FUNCTIONS_H