/*
MeTAL: My Electronic Trading Adapters Library
Copyright 2014 Jean-Cedric JOLLANT (jc@jollant.net)

This file is part of MeTAL.

MeTAL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MeTAL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MeTAL source code. If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef METAL_LSE_LSEVALUES_H
#define METAL_LSE_LSEVALUES_H_

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

	const char MessageType_ExecutionReport = '8';
	const char MessageType_HEARTBEAT = '0';
	const char MessageType_LOGON = 'A';
	const char MessageType_LOGON_REPLY = 'B';
	const char MessageType_NEW_ORDER = 'D';
	const char MessageType_ORDER_CANCEL_REQUEST = 'F';

	const OrderStatus OrderStatus_New = 0;
	const OrderStatus OrderStatus_PatiallyFilled = 1;
	const OrderStatus OrderStatus_Filled = 2;
	const OrderStatus OrderStatus_Cancelled = 4;
	const OrderStatus OrderStatus_Expired = 6;
	const OrderStatus OrderStatus_Rejected = 8;
	const OrderStatus OrderStatus_Suspended = 9;

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


#endif 
