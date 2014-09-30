/*
 * LSEValues.h
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#ifndef LSE_LSEVALUES_H_
#define LSE_LSEVALUES_H_

#include "LSETypes.h"

namespace Metal {
namespace LSE {
	const Anonymity Anonymity_ANONYMOUS = 0;
	const Anonymity Anonymity_NAMED = 1;

	const AutoCancel AutoCancel_DO_NOT_CANCEL = 0;
	const AutoCancel AutoCancel_CHECK_SYSTEM_CONFIGURATION = 1;

	const Capacity Capacity_RISKLESS_PRINCIPAL = 1;
	const Capacity Capacity_PRINCIPAL = 2;
	const Capacity Capacity_AGENCY = 3;
	const Capacity Capacity_CFD_GIVE_UP = 4;

	const ClearingAcount ClearingAccount_CLIENT = 1;
	const ClearingAcount ClearingAccount_HOUSE = 3;

	const char MessageType_LOGON = 'A';
	const char MessageType_LOGON_REPLY = 'B';
	const char MessageType_NEW_ORDER = 'D';
	const char MessageType_ORDER_CANCEL_REQUEST = 'F';

	const OrderSubType OrderSubType_ORDER = 0;
	const OrderSubType OrderSubType_PEGGED_ORDER = 5;
	const OrderSubType OrderSubType_RANDOM_PEEK_SIZE = 51;

	const OrderType OrderType_MARKET = 1;
	const OrderType OrderType_LIMIT = 2;
	const OrderType OrderType_STOP = 3;
	const OrderType OrderType_STOP_LIMIT = 4;

	const PassiveOnlyOrder PassiveOnlyOrder_NO_CONSTRAINT = 0;
	const PassiveOnlyOrder PassiveOnlyOrder_IF_NOT_MATCH_WITH_VISIBLE_CONTRA = 99;
	const PassiveOnlyOrder PassiveOnlyOrder_IF_SETTING_NEW_VISIBLE_BBO = 100;
	const PassiveOnlyOrder PassiveOnlyOrder_SETTING_NEW_BBO_OR_JOINING_EXISTING_BBO = 1;
	const PassiveOnlyOrder PassiveOnlyOrder_IF_AT_BBO_OR_WITHIN_ONE_PRICE_POINT = 2;
	const PassiveOnlyOrder PassiveOnlyOrder_IF_AT_BBO_OR_WITHIN_TWO_PRICE_POINTS = 3;

	const Side Side_BUY = 1;
	const Side Side_SELL = 2;

	const TimeInForce TimeInForce_DAY = 0;
	const TimeInForce TimeInForce_IMMEDIATE_OR_CANCEL = 3;
	const TimeInForce TimeInForce_FILL_OR_KILL = 4;
	const TimeInForce TimeInForce_AT_THE_OPENING = 5;
	const TimeInForce TimeInForce_GOOD_TILL_DATE = 6;
	const TimeInForce TimeInForce_GOOD_TILL_TIME = 8;
	const TimeInForce TimeInForce_AT_THE_CLOSE = 10;
	const TimeInForce TimeInForce_GOOD_FOR_AUCTION = 50;
	const TimeInForce TimeInForce_GOOD_FOR_INTRADAY_AUCTION = 51;
}
}


#endif /* LSE_LSEVALUES_H_ */
