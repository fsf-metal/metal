
#include <json/json.h>

#include "Field.h"
#include "NativeValues.h"

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

	this->type = getType(field);
}


Field::~Field()
{
}

FieldType Field::getType( const Json::Value &field) {
	Json::Value type = field["type"];
	if (type.isNull()) throw std::runtime_error("\"type\" is required and missing");

	if (field["size"].isNull()) throw std::runtime_error("\"size\" is required and missing");
	int size = field["size"].asInt();

	std::string strType = type.asString();
	if (!strType.compare("string")) {
		return FieldType::STRING;
	}
	else if (!strType.compare("int")){
		switch (size) {
		case 1: return INT8;
		case 2: return INT16; 
		case 4: return INT32; 
		case 8: return INT64; 
		default: throw std::runtime_error("Invalid size for type \"int\" : " + size);
		}
	}
	else if (!strType.compare("uint")){
		switch (size) {
		case 1: return UINT8; 
		case 2: return UINT16;
		case 4: return UINT32;
		case 8: return UINT64;
		default: throw std::runtime_error("Invalid size for type \"uint\" : " + size);
		}
	}
	else {
		throw std::runtime_error("Provided \"type\" is unknown " + strType);
	}

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

std::string Field::getValueCode(FieldType type, NativeValue &native) {
	switch (type) {
	case INT8: return std::to_string( native.i8);
	case INT16: return std::to_string(native.i16);
	case INT32: return std::to_string(native.i32);
	case INT64: return std::to_string(native.i64);
	case UINT8: return std::to_string(native.u8);
	case UINT16: return std::to_string(native.u16);
	case UINT32: return std::to_string(native.u32);
	case UINT64: return std::to_string(native.u64);
	case STRING: return std::string( "\"") + native.str + "\"";
	default: return "?";
	}
}


}
