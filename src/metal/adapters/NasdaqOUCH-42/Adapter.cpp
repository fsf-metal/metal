/**
 * NasdaqAdapter.cpp
 *
 *  Created on: 2014-10-14
 *      Author: Bootstrapper v0.1
 *
 */

#include <chrono>
#include "Adapter.h"
#include "Mapper.h"
#include "Codec.h"

namespace Metal {
namespace Nasdaq {

NasdaqAdapter::NasdaqAdapter() : TradingAdapter("__name__", "__uuid__") {

}

void NasdaqAdapter::encode( const NewOrderSingle& nos, Message &msg) {

	// ClOrdID std::string @1,14
	std::string strClOrdID = nos.getField(FIX::FIELD::ClOrdID);
	Codec::encode(strClOrdID, msg, 1, 14);

	// Side std::string @15,1
	std::string strSide = nos.getField(FIX::FIELD::Side);
	std::string native_strSide = mapper.sideFrom.find(strSide);
	Codec::encode(native_strSide, msg, 15, 1);

	// OrderQty int32_t @16,4
	std::string strOrderQty = nos.getField(FIX::FIELD::OrderQty);
	int32_t iOrderQty = std::stoi(strOrderQty)
	Codec::encode(iOrderQty, msg, 16);

}

void NasdaqAdapter::encodeLogon( Message &msg) {
	std::cout << "NasdaqAdapter: Logon encoding invoked but not implemented" << std::endl;
	/*	__logon_encoding__ */
}

void NasdaqAdapter::recv(const ExecutionReport &er) {
	std::cout << "NasdaqAdapter: Execution Report received but not processed" << std::endl;
}


} // namespace Nasdaq
} // namespace Metal
