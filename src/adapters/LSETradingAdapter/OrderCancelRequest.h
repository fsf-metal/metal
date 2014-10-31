/*
 * OrderCancelRequest.h
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#ifndef METAL_LSE_ORDERCANCELREQUEST_H_
#define METAL_LSE_ORDERCANCELREQUEST_H_

#include "LSETypes.h"

namespace Metal {
namespace LSE {

class OrderCancelRequest {
public:
	OrderCancelRequest();
	virtual ~OrderCancelRequest();

	ClientOrderID clientOrderID;
	Side side;
	OrderID orderId;
	OriginalClientOrderID originalClientOrderId;
	InstrumentID instrumentID;
};

} /* namespace LSE */
} /* namespace Metal */
#endif /* METAL_LSE_ORDERCANCELREQUEST_H_ */
