#ifndef __MAPPINGTABLE_H
#define __MAPPINGTABLE_H

#include <json/json.h>

namespace Bootstrapper {

using namespace std;

class MappingEntry {
public:
	MappingEntry( Json::Value &entry);

	string name;
//	NativeValue nativeValue;
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

	std::string name;
	std::vector<MappingEntry*> values;
};

}


#endif // __MAPPINGTABLE_H