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
#include "LSEValues.h"

namespace Metal {
namespace LSE {

MilleniumAdapter::MilleniumAdapter() : TradingAdapter("LSE Trading", "acba8ab0-4564-11e4-916c-0800200c9a66", new MilleniumCodec(), 3) {
	this->mCodec = (MilleniumCodec*) this->codec;
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
		this->mCodec->encode( *mappedNewOrders.at( index), msg);
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
		this->mCodec->encode( *mappedCancels.at( index), msg);
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

void MilleniumAdapter::onMessage(const Metal::LSE::ExecutionReport &nativeER) {
	//std::cout << "MilleniumAdapter: Received Native Execution Report" << std::endl;
	Metal::ExecutionReport metalER;
	MilleniumMapper::map(nativeER, metalER);
	// Propagate the normalized message
	onMessage(metalER);
}


int MilleniumAdapter::processData(const char * data, int length) {
	if (length < MilleniumCodec::HEADER_LENGTH) return 0;

	// validate first char which is always 0x02 for LSE
	if ((data[0] & 0xFF) != 0x02) {
		std::cout << Codec::formatHex((char *)data, length) << std::endl;
		throw std::runtime_error("Invalid message header " + std::to_string((int)data[0]));
	}

	int16_t msgLength = 0;
	this->mCodec->decode(data, 1, msgLength);

	// Simple check on message size to avoid garbage
	if (msgLength > 1024 || msgLength < MilleniumCodec::HEADER_LENGTH) 
		throw std::runtime_error("Invalid message size " + std::to_string(msgLength));

	// do we have enough data available?
	if (length < msgLength) return 0;

	// TODO: should we propagate the message?
	char msgType = data[3];
	//std::cout << "MilleniumAdapter: Message type=" << msgType << std::endl;

	switch (msgType) {
	case MessageType_ExecutionReport: {
		ExecutionReport er;
		this->mCodec->decode( data, er);

		// propagate this message
		onMessage(er);
	}	break;

	// don't react to other messages
	case MessageType_HEARTBEAT:
	default:
		;
	}

	return msgLength;

}

void MilleniumAdapter::sendLogon() {
	Logon logon(this->userName, this->password, "");
	Message msg;
	this->mCodec->encode(logon, msg);
	send(msg);
}

void MilleniumAdapter::sendNewOrder(const NewOrderSingle& nos) {
	NewOrder no;
	MilleniumMapper::map(nos, no);

	Message msg;
	this->mCodec->encode(no, msg);
	send(msg);
}



} // LSE::
} // Metal::
