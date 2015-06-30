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


#include <cstring>
#include "MilleniumCodec.h"
#include "LSEValues.h"

namespace Metal {
namespace LSE {

MilleniumCodec::MilleniumCodec() {
}

MilleniumCodec::~MilleniumCodec() {
}

void MilleniumCodec::decode( const char * data, ExecutionReport &er) {
	Codec::decode( data, 4, er.appID);
	decode( data, 5, er.sequenceNo);
	Codec::decode(data, 9, er.executionID, 12);
	Codec::decode(data, 21, er.clientOrderID, 20);
	Codec::decode(data, 41, er.orderID, 12);
	er.execType = data[53];
	Codec::decode( data, 54, er.executionReportRefID, 12);
	Codec::decode( data, 66, er.orderStatus);
	decode( data, 67, er.orderRejectCode);
	decode( data, 71, er.executedPrice);
	decode( data, 79, er.executedQty);
	decode( data, 83, er.leavesQty);
	Codec::decode(data, 87, er.container);
	decode(data, 88, er.displayQty);
	decode(data, 92, er.instrumentID);
	Codec::decode(data, 96, er.restatementReason);
	Codec::decode(data, 98, er.side);
	Codec::decode(data, 107, er.counterparty, 11);
	er.tradeLiquidityIndicator = data[118];
	decode(data, 119, er.tradeMatchID);
	decode(data, 127, er.transactTime);
	Codec::decode(data, 136, er.typeOfTrade);
	Codec::decode(data, 137, er.capacity);
	er.priceDifferential = data[138];
	Codec::decode(data, 139, er.publicOrderID, 12);
}

void MilleniumCodec::encode( const Logon &logon, Metal::Message &msg) {
	MilleniumCodec::encodeHeader( msg, 80, MessageType_LOGON);
	Codec::encode( logon.userName, msg, 4, 25);
	Codec::encode( logon.password, msg, 29, 25);
	Codec::encode( logon.newPassword, msg, 54, 25);
	encode( (MessageVersion)1, msg, 79);
}

void MilleniumCodec::encode( const Metal::LSE::OrderCancelRequest &ocr, Metal::Message &msg) {
	encodeHeader( msg, 73, MessageType_ORDER_CANCEL_REQUEST);
	Codec::encode( ocr.clientOrderID, msg, 4, 20);
	Codec::encode( ocr.originalClientOrderId, msg, 24, 20);
	Codec::encode( ocr.orderId, msg, 44, 12);
	Codec::encode( ocr.instrumentID, msg, 56);
	encode( ocr.side, msg, 62);
}

void MilleniumCodec::encode( const NewOrder &no, Metal::Message &msg) {
	encodeHeader( msg, NewOrder::SIZE, MessageType_NEW_ORDER);

	// Client Order ID @4 L20
	Codec::encode( no.clientOrderID, msg, 4, 20);
    // Trader ID @24 L11
	Codec::encode( no.traderID, msg, 24, 11);
    // Account @35 L10
	Codec::encode( no.account, msg, 35, 10);
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
	Codec::encode( no.expireDateTime, msg, 54);
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
	encode( length, msg, 1);
	msg.set( 3, type);

	// this is not really encoding, we are memorizing length
	msg.setLength(length);
}

void MilleniumCodec::encodeHeartBeat(Metal::Message &msg) {
	encodeHeader( msg, 4, MessageType_HEARTBEAT);
}


} /* namespace LSE */
} /* namespace Metal */
