/*
 * LSETradingAdapter.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#include "NewOrder.h"
#include "LSETradingAdapter.h"
#include "LSEMessageMapper.h"

namespace Metal {
namespace LSE {

LSETradingAdapter::LSETradingAdapter() : TradingAdapter("LSE Trading") {

}

void LSETradingAdapter::benchmark( std::vector<NewOrderSingle> &allOrders) {
	NewOrder newOrder;

	for( std::vector<NewOrderSingle>::iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
		LSEMessageMapper::map( *iter, newOrder);
	}

}

void LSETradingAdapter::recv( const ExecutionReport &er) {
	std::cout << "LSETradingAdapter: Execution Report received but not processed" << std::endl;
}

void LSETradingAdapter::send( const NewOrderSingle& nos) {
	std::cout << "LSETradingAdapter: Send Order received but not implemented" << std::endl;
}


void LSETradingAdapter::start() {

}

void LSETradingAdapter::stop() {

}

} // LSE::
} // Metal::
