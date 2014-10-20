/**
 * NasdaqMapper.cpp
 *
 *  Created on: __date__
 *      Author: __author__
 *
 */

#include <quickfix/FieldNumbers.h>
#include <metal/MetalExceptions.h>
#include "Mapper.h"

namespace Metal {
namespace Nasdaq {

/**
 * Contructor
 */
Mapper::Mapper() : Metal::Mapper() {
	// side from FIX
	sideFrom["1"] = "B";
	sideFrom["2"] = "S";
	sideFrom["5"] = "T";
	sideFrom["6"] = "E";
	// side to FIX
	sideTo["B"] = "1";
	sideTo["S"] = "2";
	sideTo["T"] = "5";
	sideTo["E"] = "6";


}

} // namespace Nasdaq
} // namespace Metal
