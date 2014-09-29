/*
 * Codec.h
 * This is this Aquis ATP Codec
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#ifndef METAL_AQUIS_CODEC_H_
#define METAL_AQUIS_CODEC_H_

#include <metal/Message.h>
#include <metal/Codec.h>
#include "Login.h"
#include "OrderAdd.h"
#include "OrderCancel.h"

namespace Metal {
namespace Aquis {

class Codec : public Metal::Codec {
public:
	Codec();
	virtual ~Codec();

	//------------------
	// Messages
	//------------------
	/**
	 * Encodes a cancel request
	 * @param oc The Order Cancel representation
	 * @param seqNum the current sequence number
	 * @param msg The destination message
	 */
	static void encode( const OrderCancel & oc, SeqNum seqNum, Message &msg);

	/**
	 * Encodes a new order
	 * @param oq The Order Add representation
	 * @param seqNum the current sequence number
	 * @param msg The destination message
	 */
	static void encode(const OrderAdd &oa, SeqNum seqNum, Message &msg);

	/**
	 * Encodes a login
	 * @param login Login representation. Must be constructed with all values
	 * @param seqNum The sequence number
	 * @param msg The destination message
	 */
	static void encode(const Login &login, SeqNum seqNum, Message &msg);

	//------------------------------------------------------------------------------------
	// Fields
	// We are relying on Codec:: little endian methods, just wrapping them for ease of use
	//------------------------------------------------------------------------------------
	inline static void encode(const uint16_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };
	inline static void encode(const uint32_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };
	inline static void encode(const uint64_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };

	/**
	 * Encode Aquis ATP Header
	 * @param length full message length
	 * @param seqNum Message sequence number
	 * @param type Message Type
	 * @param msg the output message
	 */
	inline static void encodeHeader( MsgType type, uint16_t length, SeqNum seqNum, Message &msg);
};

} /* namespace Aquis */
} /* namespace Metal */
#endif /* METAL_AQUIS_CODEC_H_ */
