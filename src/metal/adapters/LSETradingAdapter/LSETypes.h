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

	typedef int8_t Anonymity;
	typedef int8_t AppID;
	typedef int8_t AutoCancel;
	typedef int8_t Capacity;
	typedef int8_t ClearingAcount;
	typedef std::string ClientOrderID;
	typedef uint8_t Container;
	typedef char ExecType;
	typedef uint32_t ExpireDateTime;
	typedef int32_t InstrumentID;
	typedef int8_t MessageVersion;
	typedef std::string OrderID;
	typedef uint8_t OrderStatus;
	typedef int8_t OrderType;
	typedef std::string OriginalClientOrderID;
	typedef int32_t OrderRejectCode;
	typedef int8_t OrderSubType;
	typedef int8_t PassiveOnlyOrder;
	typedef int64_t Price;
	typedef char PriceDifferential;
	typedef int32_t Quantity;
	typedef uint8_t RestatementReason;
	typedef int32_t SequenceNo;
	typedef int8_t Side;
	typedef int8_t TimeInForce;
	typedef char TradeLiquidityIndicator;
	typedef uint64_t TradeMatchID;
	typedef uint64_t TransactTime;
	typedef uint8_t TypeOfTrade;


} // namespace LSE
} // namespace Metal


#endif /* METAL_LSE_LSETYPES_H_ */
