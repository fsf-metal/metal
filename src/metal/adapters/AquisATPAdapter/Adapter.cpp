/*
 * Adapter.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: jc
 */

#include <chrono>
#include "Adapter.h"

namespace Metal {
namespace Aquis {

/**
 * If you have doubts about UUID, check out header file
 */
Adapter::Adapter() : TradingAdapter("Aquis ATP", UUID) {

}

void Adapter::encode( const NewOrderSingle& nos, Message &msg) {
	std::cout << "BaseAdapter: encoding invoked but not implemented" << std::endl;
}

void Adapter::encodeLogon( Message &msg) {
	// TODO replace with proper Logon encoding
	std::cout << "BaseAdapter: Sending logon invoked but not implemented" << std::endl;
}

void Adapter::recv(const ExecutionReport &er) {
	std::cout << "BaseAdapter: Execution Report received but not processed" << std::endl;
}


} // namespace Aquis
} // namespace Metal
