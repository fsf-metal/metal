#ifndef __DESCRIPTION_FIELD_H
#define __DESCRIPTION_FIELD_H

#include <string>

#include <json/json.h>

namespace Bootstrapper {

enum FieldType { INT8, UINT8, INT16, UINT16, INT32, UINT32, INT64, UINT64, STRING};

class Field
{
public:
	Field( const Json::Value & field);
	~Field();

	/**
	* @return the c++ representation of a FieldType
	*/
	static std::string getTypeName(FieldType type);

	int position;
	int size;
	FieldType type;
	std::string name;
};

}

#endif //__DESCRIPTION_FIELD_H