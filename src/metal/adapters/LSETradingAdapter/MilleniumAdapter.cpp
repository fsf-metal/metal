/*
 * LSETradingAdapter.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#include <chrono>
#include "MilleniumAdapter.h"
#include "MilleniumMapper.h"
#include "MilleniumCodec.h"
#include "Logon.h"

namespace Metal {
namespace LSE {

MilleniumAdapter::MilleniumAdapter() : TradingAdapter("LSE Trading", "acba8ab0-4564-11e4-916c-0800200c9a66", 3) {

}

void MilleniumAdapter::benchmark( const std::vector<NewOrderSingle> &allOrders,
		std::chrono::milliseconds &mappingDuration,
		std::chrono::milliseconds &encodingDuration) {
	Metal::Message msg;

	std::vector<NewOrder *> mappedNewOrders;
	int size = allOrders.size();
	mappedNewOrders.reserve( size);

	for( int index = 0; index < size; ++index) {
        mappedNewOrders.push_back( new NewOrder());
	}

	auto t0 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		MilleniumMapper::map( allOrders.at( index), *mappedNewOrders.at( index));
	}
	auto t1 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		codec.encode( *mappedNewOrders.at( index), msg);
	}
	auto t2 = std::chrono::system_clock::now();

	// free allocated memory
	while (!mappedNewOrders.empty()) {
		delete mappedNewOrders.back();
		mappedNewOrders.pop_back();
	}

	mappingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
	encodingDuration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1);
}

void MilleniumAdapter::benchmark( const std::vector<Metal::OrderCancelRequest> &allCancels,
		std::chrono::milliseconds &mappingDuration,
		std::chrono::milliseconds &encodingDuration) {
	Metal::Message msg;

	std::vector<OrderCancelRequest *> mappedCancels;
	int size = allCancels.size();
	mappedCancels.reserve( size);

	for( int index = 0; index < size; ++index) {
        mappedCancels.push_back( new OrderCancelRequest());
	}
	auto t0 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		MilleniumMapper::map( allCancels.at( index), *mappedCancels.at( index));
	}
	auto t1 = std::chrono::system_clock::now();
	for( int index = 0; index < size; ++index) {
		this->codec.encode( *mappedCancels.at( index), msg);
	}
	auto t2 = std::chrono::system_clock::now();

	// free allocated memory
	while (!mappedCancels.empty()) {
		delete mappedCancels.back();
		mappedCancels.pop_back();
	}

	mappingDuration = std::chrono::duration_cast<std::chrono::milliseconds>( t1-t0);
	encodingDuration = std::chrono::duration_cast<std::chrono::milliseconds>( t2-t1);

}

void MilleniumAdapter::encodeHeartBeat(Message &msg) {
	codec.encodeHeartBeat(msg);
}

void MilleniumAdapter::encodeLogon(Message &msg) {
	Logon logon(this->userName, this->password, "");
	codec.encode(logon, msg);
}

void MilleniumAdapter::recv(const ExecutionReport &er) {
	std::cout << "LSETradingAdapter: Execution Report received but not processed" << std::endl;
}

void MilleniumAdapter::encode( const NewOrderSingle& nos, Message &msg) {
	NewOrder no;
	MilleniumMapper::map( nos, no);
	this->codec.encode( no, msg);
}


} // LSE::
} // Metal::
