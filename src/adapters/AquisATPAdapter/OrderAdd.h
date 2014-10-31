/*
 * OrderAdd.h
 *
 *  Created on: Sep 29, 2014
 *      Author: jc
 */

#ifndef METAL_AQUIS_ORDERADD_H_
#define METAL_AQUIS_ORDERADD_H_

#include "AquisTypes.h"

namespace Metal {
namespace Aquis {

class OrderAdd {
public:
	OrderAdd();
	virtual ~OrderAdd();

	SecurityId securityId;
	OrderType orderType;
	TimeInForce timeinForce;
	Side side;
	Quantity quantity;
	Price price;
	OrderCapacity orderCapacity;
	Account account;
	UserTag userTag;
};

} /* namespace Aquis */
} /* namespace Metal */
#endif /* METAL_AQUIS_ORDERADD_H_ */
