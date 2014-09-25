/*
 * LSEMessageEncoder.cpp
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#include <cstring>
#include "MilleniumCodec.h"
#include "LSEValues.h"

#define MIN(a,b) ( (a) > (b) ? (a) : (b))

namespace Metal {
namespace LSE {

MilleniumCodec::MilleniumCodec() {
}

MilleniumCodec::~MilleniumCodec() {
}

void MilleniumCodec::encode( const Metal::LSE::OrderCancelRequest &ocr, Metal::Message &msg) {
	encodeHeader( msg, 73, MessageType_ORDER_CANCEL_REQUEST);
	encode( ocr.clientOrderID, msg, 4, 20);
	encode( ocr.originalClientOrderId, msg, 24, 20);
	encode( ocr.orderId, msg, 44, 12);
	encode( ocr.instrumentID, msg, 56);
	encode( ocr.side, msg, 62);
}

void MilleniumCodec::encode( const NewOrder &no, Metal::Message &msg) {
	encodeHeader( msg, 97, MessageType_NEW_ORDER);

	// Client Order ID @4 L20
	encode( no.clientOrderID, msg, 4, 20);
    // Trader ID @24 L11
	encode( no.traderID, msg, 24, 11);
    // Account @35 L10
	encode( no.account, msg, 35, 10);
    // Clearing Account @45 L1
	encode( no.clearingAccount, msg, 45);
    // Instrument ID @46 L4
	encode( no.instrumentID, msg, 46);
	// Reserved Field @50 L1
	// Reserved Field @51 L1
    // OrderType @52 L1
	encode( no.orderType, msg, 52);
    // Time in Force @53 L1
	encode( no.timeInForce, msg, 53);
    // Expire date @54 L4
	encode( no.expireDateTime, msg, 54);
    // Side &58 L1
	encode( no.side, msg, 58);
    // Order Qty @59 L4
	encode( no.orderQty, msg, 59);
    // Display Qty @63 L4
	encode( no.displayQty, msg, 63);
    // Limit Price @67 L8
	encode( no.limitPrice, msg, 67);
    // Capacity @75 L1
	encode( no.capacity, msg, 75);
    // Auto Cancel @76 L1
	encode( no.autoCancel, msg, 76);
    // Order Sub Type @77 L1
	encode( no.orderSubType, msg, 77);
    // Anonymity @78 L1
	encode( no.anonymity, msg, 78);
    // Stopped price @79 L8
	encode( no.stoppedPrice, msg, 79);
    // Passive Only Order @87 L1
	encode( no.passiveOnlyOrder, msg, 87);
    // Reserved Field @88L 9
}

void MilleniumCodec::encodeHeader( Metal::Message &msg, int16_t length, char type) {
	msg.set( 0, (char)2);
	encode( length, msg, length);
	msg.set( 3, type);
}

void MilleniumCodec::encode( const std::string &str, Message & msg, int position, int maxLength) {
	msg.set( position, str, maxLength);
}

void MilleniumCodec::encode( const int8_t &i, Metal::Message & msg, int position) {
	msg.set( position, i);
}

void MilleniumCodec::encode( const int16_t &i, Metal::Message & msg, int position) {
	msg.set( position, ( ( i & 0xFF00) >> 8));
	msg.set( ++position, ( i & 0x00FF));
}

void MilleniumCodec::encode( const int32_t &i, Metal::Message & msg, int position) {
	msg.set(  position, ( ( i & 0xFF000000) >> 24));
	msg.set(++position, ( ( i & 0x00FF0000) >> 16));
	msg.set(++position, ( ( i & 0x0000FF00) >> 8));
	msg.set(++position,   ( i & 0x000000FF));
}

void MilleniumCodec::encode( const uint32_t &i, Metal::Message & msg, int position) {
	encode( (int32_t&)i, msg, position);
}

void MilleniumCodec::encode( const int64_t &i, Metal::Message & msg, int position) {
	msg.set(  position, ( ( i & 0xFF00000000000000) >> 56));
	msg.set(++position, ( ( i & 0x00FF000000000000) >> 48));
	msg.set(++position, ( ( i & 0x0000FF0000000000) >> 40));
	msg.set(++position, ( ( i & 0x000000FF00000000) >> 32));
	msg.set(++position, ( ( i & 0x00000000FF000000) >> 24));
	msg.set(++position, ( ( i & 0x0000000000FF0000) >> 16));
	msg.set(++position, ( ( i & 0x000000000000FF00) >> 8));
	msg.set(++position,   ( i & 0x00000000000000FF));
}

} /* namespace LSE */
} /* namespace Metal */
