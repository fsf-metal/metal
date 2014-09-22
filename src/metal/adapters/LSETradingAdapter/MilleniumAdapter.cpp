/*
 * LSETradingAdapter.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#include "MilleniumAdapter.h"
#include "LSEMessageMapper.h"

namespace Metal {
namespace LSE {

MilleniumAdapter::MilleniumAdapter() : TradingAdapter("LSE Trading") {

}

void MilleniumAdapter::benchmark( std::vector<NewOrderSingle> &allOrders) {
	NewOrder newOrder;

	for( std::vector<NewOrderSingle>::iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
		LSEMessageMapper::map( *iter, newOrder);
		// TODO add encoding
	}

}

void MilleniumAdapter::benchmark(std::vector<Metal::OrderCancelRequest> &allCancels) {
	Metal::LSE::OrderCancelRequest ocr;

	for( std::vector<Metal::OrderCancelRequest>::iterator iter = allCancels.begin(); iter != allCancels.end(); ++iter) {
		LSEMessageMapper::map( *iter, ocr);
		// TODO add encoding
	}
}

void MilleniumAdapter::recv(const ExecutionReport &er) {
	std::cout << "LSETradingAdapter: Execution Report received but not processed" << std::endl;
}

void MilleniumAdapter::send( const NewOrderSingle& nos) {
	std::cout << "LSETradingAdapter: Send Order received but not implemented" << std::endl;
}


void MilleniumAdapter::start() {

}

void MilleniumAdapter::stop() {

}

} // LSE::
} // Metal::
