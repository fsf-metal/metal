#ifndef __METAL_FUNCTIONS_H
#define __METAL_FUNCTIONS_H

#include <string>
#include <iostream>

#include <json/json.h>

#include "Field.h"

namespace Bootstrapper {

	class Functions
	{
	public:
		Functions();
		~Functions();
		static void copyFrom(const std::string &fixFieldName, const Field &field, std::stringstream &sourceCode);
	};

}

#endif // __METAL_FUNCTIONS_H