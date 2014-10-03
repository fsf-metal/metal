/*
 * __namespace__Adapter.cpp
 *
 *  Created on: __date__
 *      Author: Bootstraper
 *
 */

#include <chrono>
#include "__namespace__Adapter.h"
#include "__namespace__Mapper.h"
#include "__namespace__Codec.h"

namespace Metal {
namespace __namespace__ {

__namespace__Adapter::__namespace__Adapter() : TradingAdapter("__name__", "__uuid__") {

}

void __namespace__Adapter::encode( const NewOrderSingle& nos, Message &msg) {
	std::cout << "__namespace__Adapter: encoding invoked but not implemented" << std::endl;
	__nos-encoding__
}

void __namespace__Adapter::encodeLogon( Message &msg) {
	std::cout << "__namespace__Adapter: Sending logon invoked but not implemented" << std::endl;
	__logon_encoding__
}

void __namespace__Adapter::recv(const ExecutionReport &er) {
	std::cout << "__namespace__Adapter: Execution Report received but not processed" << std::endl;
}


} // namespace __namespace__
} // namespace Metal
