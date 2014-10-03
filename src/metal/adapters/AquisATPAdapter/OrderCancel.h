/*
 * OrderCancel.h
 *
 *  Created on: Sep 29, 2014
 *      Author: jc
 */

#ifndef METAL_ACQUIS_ORDERCANCEL_H_
#define METAL_ACQUIS_ORDERCANCEL_H_

#include "AquisTypes.h"

namespace Metal {
namespace Aquis {


class OrderCancel {
public:
	OrderCancel();
	virtual ~OrderCancel();

	OrderRef orderRef;
	UserTag userTag;
};

} /* namespace Aquis */
} /* namespace Metal */
#endif /* METAL_ACQUIS_ORDERCANCEL_H_ */
