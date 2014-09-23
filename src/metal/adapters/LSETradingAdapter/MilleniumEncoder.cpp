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

void MilleniumEncoder::encode( const NewOrder &newOrder, Metal::Message &msg) {
	encodeHeader( msg, 97, MessageType_NEW_ORDER);

	// TODO Encode all these fields
	// Client Order ID @4 L20
    // Trader ID @24 L11
    // Account @35 L10
    // Clearing Account @45 L1
    // Instrument ID @46 L4
	// Reserved Field @50 L1
	// Reserved Field @51 L1
    // OrderType @52 L1
    // Time in Force @53 L1
    // Expire date @54 L4
    // Side &58 L1
    // Order Qty @59 L4
    // Display Qty @63 L4
    // Limit Price @67 L8
    // Capacity @75 L1
    // Auto Cancel @76 L1
    // Order Sub Type @77 L1
    // Anonymity @78 L1
    // Stopped price @79 L8
    // Passive Only Order @87 L1
    // Reservered Field @88L 9
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
