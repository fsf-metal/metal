#ifndef __MAPPINGTABLE_H
#define __MAPPINGTABLE_H

#include <cstdint>

#include <json/json.h>

#include "Field.h"
#include "NativeValues.h"

namespace Bootstrapper {

using namespace std;

class MappingEntry {
public:
	MappingEntry( Json::Value &entry);

	string name;
	NativeValue nativeValue;
	string fixValue;
};


class MappingTable
{
public:
	/**
	 * May throw an exception if the inbound json is incorretly formatted
	 */
	MappingTable( Json::Value source);
	~MappingTable();

	void addDeclaration(stringstream & ss);
	/**
	 * Format initialization source code
	 * @param ss output stringstream where source code will be appended
	 */
	void addInitialization(stringstream & ss);

	std::string name;
	std::vector<MappingEntry*> values;
	FieldType fieldType;
};

}


#endif // __MAPPINGTABLE_H