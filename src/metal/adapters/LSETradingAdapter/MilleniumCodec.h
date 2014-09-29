/*
 * LSEMessageEncoder.h
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#ifndef METAL_LSE_LSEMESSAGEENCODER_H_
#define METAL_LSE_LSEMESSAGEENCODER_H_

#include <metal/Message.h>
#include <metal/Codec.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"
#include "Logon.h"

namespace Metal {
namespace LSE {

class MilleniumCodec : public Codec {
public:
	MilleniumCodec();
	virtual ~MilleniumCodec();

	//------------------
	// Messages
	//------------------
	/**
	 * Encode a cancel request
	 * @param ocr The Order Cancel Request representation
	 * @param msg The destination message
	 */
	static void encode( const OrderCancelRequest & ocr, Message &msg);

	/**
	 * Encode a new order
	 * @param no The New Order representation
	 * @param msg The destination message
	 */
	static void encode(const NewOrder &no, Message &msg);

	/**
	 * Encode a logon
	 * @param logon Logon representation. Must be constructed with all values
	 * @param msg The destination message
	 */
	static void encode(const Logon &logon, Message &msg);

	//------------------------------------------------------------------------------------
	// Fields
	// We are relying on Codec:: little endian methods, just wrapping them for ease of use
	//------------------------------------------------------------------------------------
	inline static void encode(const int16_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };
	inline static void encode(const int32_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };
	inline static void encode(const int64_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };

	inline static void encodeHeader( Message &msg, int16_t length, char type);
};

} /* namespace LSE */
} /* namespace Metal */
#endif /* METAL_LSE_LSEMESSAGEENCODER_H_ */
