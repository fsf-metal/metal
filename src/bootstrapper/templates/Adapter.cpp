/**
 * __namespace__Adapter.cpp
 *
 *  Created on: __date__
 *      Author: __author__
 *
 */

#include <chrono>
#include "Adapter.h"
#include "Mapper.h"
#include "Codec.h"

namespace Metal {
namespace __namespace__ {

__namespace__Adapter::__namespace__Adapter() : TradingAdapter("__name__", "__uuid__") {

}

void __namespace__Adapter::encode( const NewOrderSingle& nos, Message &msg) {
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
