/*
 * NewOrder.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#include "NewOrder.h"
#include "LSEValues.h"

namespace Metal {
namespace LSE {

using namespace std;

NewOrder::NewOrder() : clientOrderID(""), traderID(""), account("") {
	this->clearingAccount = ClearingAccount_CLIENT;
	this->instrumentID = 0;
	this->orderType = OrderType_LIMIT;
	this->timeInForce = TimeInForce_DAY;
	this->orderQty = 0;
	this->expireDateTime = 0;
	this->side = Side_BUY;
	this->orderQty = 0;
	this->displayQty = 0;
	this->limitPrice = 0;
	this->capacity = Capacity_AGENCY;
	this->autoCancel = AutoCancel_DO_NOT_CANCEL;
	this->orderSubType = OrderSubType_ORDER;
	this->anonymity = Anonymity_ANONYMOUS;
	this->stoppedPrice = 0;
	this->passiveOnlyOrder = PassiveOnlyOrder_NO_CONSTRAINT;
}

NewOrder::~NewOrder() {
	// TODO Auto-generated destructor stub
}

} /* namespace LSE */
} /* namespace Metal */
