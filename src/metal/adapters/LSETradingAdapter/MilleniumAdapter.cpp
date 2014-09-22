/*
 * LSETradingAdapter.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#include "MilleniumAdapter.h"
#include "MilleniumMapper.h"
#include "MilleniumEncoder.h"

namespace Metal {
namespace LSE {

MilleniumAdapter::MilleniumAdapter() : TradingAdapter("LSE Trading") {

}

void MilleniumAdapter::benchmark( const std::vector<NewOrderSingle> &allOrders, bool mappingOnly) {
	NewOrder newOrder;

	if( mappingOnly) {
		for( std::vector<NewOrderSingle>::const_iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
			MilleniumMapper::map( *iter, newOrder);
			// TODO add encoding
		}
	} else {
		for( std::vector<NewOrderSingle>::const_iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
			MilleniumMapper::map( *iter, newOrder);
			// TODO add encoding
		}
	}

}

void MilleniumAdapter::benchmark( const std::vector<Metal::OrderCancelRequest> &allCancels, bool mappingOnly) {
	Metal::LSE::OrderCancelRequest ocr;
	Metal::Message msg;

	if( mappingOnly) {
		for( std::vector<Metal::OrderCancelRequest>::const_iterator iter = allCancels.begin(); iter != allCancels.end(); ++iter) {
			MilleniumMapper::map( *iter, ocr);
		}
	} else { // perform mapping and encoding
		for( std::vector<Metal::OrderCancelRequest>::const_iterator iter = allCancels.begin(); iter != allCancels.end(); ++iter) {
			MilleniumMapper::map( *iter, ocr);
			MilleniumEncoder::encode( ocr, msg);
		}
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
