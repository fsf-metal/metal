/*
 * LSETypes.h
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#ifndef METAL_LSE_LSETYPES_H_
#define METAL_LSE_LSETYPES_H_

#include <string>
#include <cstdint>

namespace Metal {
namespace LSE {

	typedef int64_t Price;
	typedef int8_t Side;
	typedef std::string ClientOrderID;
	typedef std::string OrderID;
	typedef std::string OriginalClientOrderID;
	typedef int32_t InstrumentID;
	typedef int8_t OrderType;
	typedef int8_t TimeInForce;
	typedef int8_t ClearingAcount;
	typedef uint32_t ExpireDateTime;
	typedef int32_t OrderQty;
	typedef int32_t DisplayQty;
	typedef int8_t Capacity;
	typedef int8_t AutoCancel;
	typedef int8_t OrderSubType;
	typedef int8_t Anonymity;
	typedef int8_t PassiveOnlyOrder;
	typedef int8_t MessageVersion;

} // namespace LSE
} // namespace Metal


#endif /* METAL_LSE_LSETYPES_H_ */
