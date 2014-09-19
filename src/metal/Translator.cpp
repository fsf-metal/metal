/*
 * Translator.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: jc
 */

#include <string>
#include "Translator.h"
#include "quickfix/FixValues.h"

namespace Metal {

Translator::Translator() {
	// TODO Auto-generated constructor stub

}

Translator::~Translator() {
	// TODO Auto-generated destructor stub
}

const std::string Translator::field( const FIX::OrdStatus &ordStatus) {
	using namespace FIX;
	switch( ordStatus) {
		case OrdStatus_FILLED: return "Filled";
		case OrdStatus_PENDING_REPLACE: return "Pending Replace";
		case OrdStatus_CANCELED: return "Canceled";
		case OrdStatus_ACCEPTED_FOR_BIDDING: return "Accepted for Bidding";
		case OrdStatus_SUSPENDED: return "Suspended";
		case OrdStatus_REJECTED: return "Rejected";
		case OrdStatus_PARTIALLY_FILLED: return "Partially Filled";
		case OrdStatus_EXPIRED: return "Expired";
		case OrdStatus_REPLACED: return "Replaced";
		case OrdStatus_DONE_FOR_DAY: return "Done for Day";
		default: return "Unknown?";
	}
}


} /* namespace Metal */
