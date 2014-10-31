/*
 * Codec.cpp // TODO replace with your own name
 * This code can be used as bootstrap to create a new adapter
 *
 *  Created on: Sep 29, 2014
 *      Author: jc
 */

#include <cstring>
#include "Codec.h"
#include "Login.h"
#include "AquisValues.h"

namespace Metal {
namespace Aquis {

Codec::Codec() {
}

Codec::~Codec() {
}

void Codec::encode(const Login &login, SeqNum seqNum, Message &msg) {
	encodeHeader( 47, MessageType_LOGIN, seqNum, msg);
	Codec::encode( login.protocolVersion, msg, 7);
	Metal::Codec::encode( login.senderId, msg, 9, 16);
	Metal::Codec::encode( login.password, msg, 25, 16);
	Codec::encode( login.inactivityTimeout, msg, 41);
	Codec::encode( login.atqSeqNo, msg, 43);
}

void Codec::encode( const OrderAdd& oa, SeqNum seqNum, Message &msg) {
	encodeHeader( 34, MessageType_ORDER_ADD, seqNum, msg);
	Codec::encode( oa.securityId, msg, 7);
	Metal::Codec::encode( oa.orderType, msg, 9);
	Metal::Codec::encode( oa.timeinForce, msg, 10);
	Metal::Codec::encode( oa.side, msg, 11);
	Codec::encode( oa.quantity, msg, 12);
	encode( oa.price, msg, 16);
	Metal::Codec::encode( oa.orderCapacity, msg, 24);
	Metal::Codec::encode( oa.account, msg, 25);
	Codec::encode( oa.userTag, msg, 26);
}

void Codec::encode( const OrderCancel& oc, SeqNum seqNum, Message &msg) {
	encodeHeader( 34, MessageType_ORDER_ADD, seqNum, msg);
	Codec::encode( oc.orderRef, msg, 7);
	Codec::encode( oc.userTag, msg, 11);
}

void Codec::encodeHeader( MsgType type, uint16_t length, SeqNum seqNum, Message &msg){
	Codec::encode( length, msg, 0);
	Metal::Codec::encode( type, msg, 2);
	Codec::encode( seqNum, msg, 3);
}


} /* namespace Aquis */
} /* namespace Metal */
