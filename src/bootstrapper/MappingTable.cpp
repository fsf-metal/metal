#include <sstream>
#include <cstring>

#include "MappingTable.h"
#include "Field.h"

namespace Bootstrapper {

MappingEntry::MappingEntry(Json::Value &entry) {
	if (entry["name"].isNull()) throw std::runtime_error("MappingEntry: \"name\" is required and missing");
	this->name = entry["name"].asString();

	if (entry["native"].isNull()) throw std::runtime_error("MappingEntry: \"native\" is required and missing");
	if (entry["native"].isString()) strncpy(this->nativeValue.str, entry["native"].asCString(), sizeof(this->nativeValue.str));
	else this->nativeValue.i16 = entry["native"].asInt();

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

void MappingTable::addInitialization(stringstream &ss) {
	ss << "\t// " << this->name << " from FIX" << endl;
	for (vector<MappingEntry*>::iterator iter = this->values.begin(); iter != this->values.end(); ++iter) {
		MappingEntry* pME = *iter;
		ss << "\t" << this->name << "From[\"" << pME->fixValue << "\"] = " << Field::getValueCode( this->fieldType, pME->nativeValue) << ";" << endl;
	}
	ss << endl;
	ss << "\t// " << this->name << " to FIX" << endl;
	for (vector<MappingEntry*>::iterator iter = this->values.begin(); iter != this->values.end(); ++iter) {
		MappingEntry* pME = *iter;
		ss << "\t" << this->name << "To[" << Field::getValueCode(this->fieldType, pME->nativeValue) << "] = \"" << pME->fixValue << "\";" << endl;
	}
	ss << endl;
}


}
