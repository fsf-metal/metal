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

const std::string MilleniumAdapter::NAME = "LSE Trading";
const std::string MilleniumAdapter::UUID = "acba8ab0-4564-11e4-916c-0800200c9a66";

MilleniumAdapter::MilleniumAdapter() : TradingAdapter( NAME, UUID, 3) {
	this->codec = new MilleniumCodec();
}

void MilleniumAdapter::onMessage(const Metal::LSE::ExecutionReport &nativeER) {
	//std::cout << "MilleniumAdapter: Received Native Execution Report" << std::endl;
	Metal::ExecutionReport metalER;
	MilleniumMapper::map(nativeER, metalER);

	// Propagate the normalized message
	onExecutionReport(metalER);
}


int MilleniumAdapter::processData(const char * data, int length) {
	if (length < MilleniumCodec::HEADER_LENGTH) return 0;

	// validate first char which is always 0x02 for LSE
	if ((data[0] & 0xFF) != 0x02) {
		std::cout << Codec::formatHex((char *)data, length) << std::endl;
		throw std::runtime_error("Invalid message header " + std::to_string((int)data[0]));
	}

	int16_t msgLength = 0;
	this->codec->decode(data, 1, msgLength);

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
		this->codec->decode( data, er);

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

void MilleniumAdapter::sendCancel(const Metal::OrderCancelRequest& ocr) {
	OrderCancelRequest nativeOCR;
	MilleniumMapper::map(ocr, nativeOCR);
	send(nativeOCR);
}

void MilleniumAdapter::sendHeartBeat() {
	Logon logon( this->userName, this->password);
	send(logon);
}

void MilleniumAdapter::sendLogon() {
	Logon logon(this->userName, this->password, "");
	Message msg;
	this->codec->encode(logon, msg);
	send(msg);
}

void MilleniumAdapter::sendNewOrder(const NewOrderSingle& nos) {
	NewOrder no;
	MilleniumMapper::map(nos, no);

	Message msg;
	this->codec->encode(no, msg);
	send(msg);
}



} // LSE::
} // Metal::
