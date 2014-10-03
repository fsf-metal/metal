/*
 * Translator.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: jc
 */

#include <string>
#include <metal/Translator.h>
#include <quickfix/FixValues.h>

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

const std::string Translator::field(const FIX::ExecType &execType) {
	using namespace FIX;
	switch (execType) {
	case ExecType_CALCULATED: return "Calculated";
	case ExecType_CANCELED: return "CanceLled";
//	case ExecType_CANCELLED: return "Cancelled";
	case ExecType_DONE_FOR_DAY: return "Done For Day";
	case ExecType_EXPIRED: return "Expired";
	case ExecType_FILL: return "Fill";
	case ExecType_NEW: return "New";
	case ExecType_ORDER_STATUS: return "Order Status";
	case ExecType_PARTIAL_FILL: return "Partial Fill";
	case ExecType_PENDING_CANCEL: return "Pending Cancel/Replace";
//	case ExecType_PENDING_CANCEL_REPLACE:
	case ExecType_PENDING_NEW: return "Pending New";
	case ExecType_PENDING_REPLACE: return "Pending Replace";
	case ExecType_REJECTED: return "Rejected";
	case ExecType_REPLACE: return "Replace";
//	case ExecType_REPLACED: return "Replaced";
	case ExecType_RESTATED: return "Restated";
	case ExecType_STOPPED: return "Stopped";
	case ExecType_SUSPENDED: return "Suspended";
	case ExecType_TRADE: return "Trade";
	case ExecType_TRADE_CANCEL: return "Trade Cancel";
	case ExecType_TRADE_CORRECT: return "Trade Correct";
	case ExecType_TRADE_HAS_BEEN_RELEASED_TO_CLEARING: return "Trade Released To Clearing";
	case ExecType_TRADE_IN_A_CLEARING_HOLD: return "Trading in Clearing Hold";
	case ExecType_TRIGGERED_OR_ACTIVATED_BY_SYSTEM: return "Triggered/Activated by System";
	default: return "Unknown?";
	}
}

const std::string Translator::field(const FIX::Side &side) {
	using namespace FIX;
	switch (side) {
	case Side_AS_DEFINED: return "As Defined";
	case Side_BORROW: return "Borrow";
	case Side_BUY: return "Buy";
	case Side_BUY_MINUS: return "Buy Minus";
	case Side_CROSS: return "Cross";
	case Side_CROSS_SHORT: return "Cross Short";
	case Side_CROSS_SHORT_EXEMPT: return "Cross Short Exempt";
	case Side_LEND: return "Lend";
	case Side_OPPOSITE: return "Opposite";
	case Side_REDEEM: return "Redeem";
	case Side_SELL: return "Sell";
	case Side_SELL_PLUS: return "Sell Plus";
	case Side_SELL_SHORT: return "Sell Short";
	case Side_SELL_SHORT_EXEMPT: return "Sell Short Exempt";
	case Side_SUBSCRIBE: return "Subscribe";
	case Side_UNDISCLOSED: return "Undisclosed";
	default: return "Unknown?";
	}
}


} /* namespace Metal */
