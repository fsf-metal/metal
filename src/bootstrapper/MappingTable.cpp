#include <sstream>

#include "MappingTable.h"
#include "Field.h"

/**
"mappingTables": [
{   "name": "side",
"type": "string",
"size": 1,
"values": [
{"name":"Buy", "native":"B", "FIX":"1"},
{"name":"Sell", "native":"S", "FIX":"2"},
{"name":"SellShort", "native":"T", "FIX":"5"},
{"name":"SellShortExempt", "native":"E", "FIX":"6"}
]
}]

*/

namespace Bootstrapper {

MappingEntry::MappingEntry(Json::Value &entry) {
	if (entry["name"].isNull()) throw std::runtime_error("MappingEntry: \"name\" is required and missing");
	this->name = entry["name"].asString();

	if (entry["native"].isNull()) throw std::runtime_error("MappingEntry: \"native\" is required and missing");
//	this->nativeValue = new NativeValue();

	if (entry["FIX"].isNull()) throw std::runtime_error("MappingEntry: \"FIX\" is required and missing");
	this->fixValue = entry["FIX"].asString();
}


MappingTable::MappingTable( Json::Value source) {
	if (source["name"].isNull()) throw std::runtime_error("MappingTable: \"name\" is required and missing");
	this->name = source["name"].asString();
	this->fieldType = Field::getType(source);

	// loop throgh values
	Json::Value values = source["values"];
	if (values.isNull()) throw std::runtime_error("MappingTable: \"values\" are requireed and missing");
	for (unsigned int index = 0; index < values.size(); ++index) {
		this->values.push_back(new MappingEntry( values[index]));
	}
}


MappingTable::~MappingTable(){
}

void MappingTable::addDeclaration(stringstream & ss) {
	ss << "\tstd::map <std::string," << Field::getTypeName( this->fieldType) << "> " << this->name << "From;" << endl;
}


}
