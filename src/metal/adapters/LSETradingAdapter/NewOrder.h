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

	// TODO : Add Type safe members
	std::string clientOrderID;
	std::string traderID;
	std::string account;
	char clearingAccount;
	std::string instrumentID;
	char orderType;
	char timeInForce;
	long price;
	Side side;
	Quantity quantity;
	Quantity displayQty;
};

} /* namespace LSE */
} /* namespace Metal */

#endif /* METAL_LSE_NEWORDER_H_ */
