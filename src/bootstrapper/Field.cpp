
#include <json/json.h>

#include "Field.h"


namespace Bootstrapper {

Field::Field( const Json::Value & field) :size(0), position(0) {
	Json::Value size = field["size"];
	if (size.isNull()) throw std::runtime_error("\"size\" is required and missing");
	this->size = size.asInt();

	Json::Value position = field["pos"];
	if (position.isNull()) throw std::runtime_error("\"position\" is required and missing");
	this->position = position.asInt();

	Json::Value name = field["name"];
	if (name.isNull()) throw std::runtime_error("\"name\" is required and missing");
	this->name = name.asString();

	Json::Value type = field["type"];
	if (type.isNull()) throw std::runtime_error("\"type\" is required and missing");
	std::string strType = type.asString();
	if ( !strType.compare( "string")) {
		this->type = FieldType::STRING;
	} else if( !strType.compare("int")){
		switch (this->size) {
		case 1: this->type = INT8; break;
		case 2: this->type = INT16; break;
		case 4: this->type = INT32; break;
		case 8: this->type = INT64; break;
		default: throw std::runtime_error("Invalid size for type \"int\" : " + this->size);
		}
	} else if (!strType.compare("uint")){
		switch (this->size) {
		case 1: this->type = UINT8; break;
		case 2: this->type = UINT16; break;
		case 4: this->type = UINT32; break;
		case 8: this->type = UINT64; break;
		default: throw std::runtime_error("Invalid size for type \"uint\" : " + this->size);
		}
	} else {
		throw std::runtime_error("Provided \"type\" is unknown " + strType);
	}
}


Field::~Field()
{
}


std::string Field::getTypeName( FieldType type) {
	switch (type) {
	case INT8: return "int8_t";
	case INT16: return "int16_t";
	case INT32: return "int32_t";
	case INT64: return "int64_t";
	case UINT8: return "uint8_t";
	case UINT16: return "uint16_t";
	case UINT32: return "uint32_t";
	case UINT64: return "uint64_t";
	case STRING: return "std::string";
	default: return "?";
	}
}


}
