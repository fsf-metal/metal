/*
 * LSEMessageEncoder.cpp
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#include <cstring>
#include "MilleniumEncoder.h"
#include "LSEValues.h"

#define MIN(a,b) ( (a) > (b) ? (a) : (b))

namespace Metal {
namespace LSE {

MilleniumEncoder::MilleniumEncoder() {
}

MilleniumEncoder::~MilleniumEncoder() {
}

void MilleniumEncoder::encode( const OrderCancelRequest &ocr, Metal::Message &msg) {
	encodeHeader( msg, 73, MessageType_ORDER_CANCEL_REQUEST);
	encodeString( ocr.clientOrderID, msg, 4, 20);
	encodeString( ocr.originalClientOrderId, msg, 24, 20);
	encodeString( ocr.orderId, msg, 44, 12);
	encodeInt32( ocr.instrumentID, msg, 56);
	encodeInt8( ocr.side, msg, 62);
}

void MilleniumEncoder::encodeHeader( Metal::Message &msg, int16_t length, char type) {
	msg.set( 0, (char)2);
	encodeInt16( length, msg, length);
	msg.set( 3, type);
}

void MilleniumEncoder::encodeString( const std::string &str, Message & msg, int position, int maxLength) {
	msg.set( position, str, maxLength);
}

void MilleniumEncoder::encodeInt8( const int8_t &i, Metal::Message & msg, int position) {
	msg.set( position, i);
}

void MilleniumEncoder::encodeInt16( const int16_t &i, Metal::Message & msg, int position) {
	msg.set( position, ( ( i & 0xFF00) >> 8));
	msg.set( ++position, ( i & 0xFF));
}

/**
 * Little endian 32 bits
 */
void MilleniumEncoder::encodeInt32( const int32_t &i, Metal::Message & msg, int position) {
	msg.set(  position, ( ( i & 0xFF000000) >> 24));
	msg.set(++position, ( ( i & 0xFF0000) >> 16));
	msg.set(++position, ( ( i & 0xFF00) >> 8));
	msg.set(++position,   ( i & 0xFF));
}

} /* namespace LSE */
} /* namespace Metal */
