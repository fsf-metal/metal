/*
 * LSETradingAdapter.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#include <chrono>
#include "BaseAdapter.h"
#include "BaseMapper.h"
#include "BaseCodec.h"

namespace Metal {
namespace Base { // TODO replace with your own

/**
 * If you have doubts about UUID, check out header file
 */
BaseAdapter::BaseAdapter() : TradingAdapter("Base Trading Adapter (for dev purpose)", UUID) {

}

void BaseAdapter::encode( const NewOrderSingole& nos, Message &msg) {
	std::cout << "BaseAdapter: encoding invoked but not implemented" << std::endl;
}

void BaseAdapter::encodeLogon( Message &msg) {
	// TODO replace with proper Logon encoding
	std::cout << "BaseAdapter: Sending logon invoked but not implemented" << std::endl;
}

void BaseAdapter::recv(const ExecutionReport &er) {
	std::cout << "BaseAdapter: Execution Report received but not processed" << std::endl;
}


} // namespace Base TODO put your own
} // namespace Metal
