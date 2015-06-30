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

#ifndef METAL_LSE_EXECUTIONREPORT_H_
#define METAL_LSE_EXECUTIONREPORT_H_

#include <string>
#include "LSETypes.h"

namespace Metal {
namespace LSE {

/**
 * This class represents a native LSE Execution Report message
 */
class ExecutionReport {
public:
	ExecutionReport();
	virtual ~ExecutionReport();

	static const int SIZE = 151;

	AppID appID;
	SequenceNo sequenceNo;
	std::string executionID;
	std::string clientOrderID;
	std::string orderID;
	ExecType execType;
	std::string executionReportRefID;
	OrderStatus orderStatus;
	OrderRejectCode orderRejectCode;
	Price executedPrice;
	Quantity executedQty;
	Quantity leavesQty;
	Container container;
	Quantity displayQty;
	InstrumentID instrumentID;
	RestatementReason restatementReason;
	Side side;
	std::string counterparty;
	TradeLiquidityIndicator tradeLiquidityIndicator;
	TradeMatchID tradeMatchID;
	TransactTime transactTime;
	TypeOfTrade typeOfTrade;
	Capacity capacity;
	PriceDifferential priceDifferential;
	std::string publicOrderID;
};

} /* namespace LSE */
} /* namespace Metal */

#endif /* METAL_LSE_EXECUTIONREPORT_H_ */
