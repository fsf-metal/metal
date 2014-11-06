/*
MeTAL: My Electronic Trading Adapters Library
Copyright 2014 Jean-Cedric JOLLANT (jc@jollant.net)

This file is part of MeTAL.

MeTAL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MeTAL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MeTAL source code. If not, see <http://www.gnu.org/licenses/>.

*/

#include <chrono>
#include "MilleniumAdapter.h"
#include "MilleniumCodec.h"
#include "Logon.h"
#include "LSEValues.h"

namespace Metal {
namespace LSE {

const std::string MilleniumAdapter::NAME = "LSE Trading";
const std::string MilleniumAdapter::UUID = "acba8ab0-4564-11e4-916c-0800200c9a66";

MilleniumAdapter::MilleniumAdapter( std::string userNameParam, std::string passwordParam) 
	: TradingAdapter( NAME, UUID, 3), userName( userNameParam), password( passwordParam) {
	this->codec = new MilleniumCodec();
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

void MilleniumAdapter::sendHeartBeat() {
	Message heartbeat;
	this->codec->encodeHeartBeat(heartbeat);
	send(heartbeat);
}

void MilleniumAdapter::sendLogon() {
	Logon logon(this->userName, this->password, "");
	Message msg;
	this->codec->encode(logon, msg);
	send(msg);
}



} // LSE::
} // Metal::
