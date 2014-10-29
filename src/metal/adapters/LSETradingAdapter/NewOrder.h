/*
 * NewOrder.h
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#ifndef METAL_LSE_NEWORDER_H_
#define METAL_LSE_NEWORDER_H_

#include <string>
#include "LSETypes.h"

namespace Metal {
namespace LSE {

class NewOrder {
public:
	NewOrder();
	virtual ~NewOrder();

	static const int SIZE = 97;

	// TODO : Add Type safe members
	std::string clientOrderID;
	std::string traderID;
	std::string account;
	ClearingAcount clearingAccount;
	InstrumentID instrumentID;
	OrderType orderType;
	TimeInForce timeInForce;
	ExpireDateTime expireDateTime;
	Side side;
	OrderQty orderQty;
	DisplayQty displayQty;
	Price limitPrice;
	Capacity capacity;
	AutoCancel autoCancel;
	OrderSubType orderSubType;
	Anonymity anonymity;
	Price stoppedPrice;
	PassiveOnlyOrder passiveOnlyOrder;
};

} /* namespace LSE */
} /* namespace Metal */

#endif /* METAL_LSE_NEWORDER_H_ */
