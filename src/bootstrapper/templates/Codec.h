/*
 * BaseAdapter.h
 * This header is provided as an example it is not functional
 * Please look for TODO tags
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#ifndef METAL_BASE_BASEADAPTER_H_ // TODO use your own name
#define METAL_BASE_BASEADAPTER_H_ // TODO use your own name

#include <metal/Message.h>
#include <metal/Codec.h>

namespace Metal {
namespace Base { // TODO replace with your own namespace

class BaseCodec : public Codec {
public:
	BaseCodec();
	virtual ~BaseCodec();

	//------------------
	// Messages
	//------------------
	/**
	 * Encodes a cancel request
	 * @param ocr The Order Cancel Request representation
	 * @param msg The destination message
	 */
	static void encode( const OrderCancelRequest & ocr, Message &msg);

	/**
	 * Encodes a new order
	 * @param no The New Order representation
	 * @param msg The destination message
	 */
	static void encode(const NewOrder &no, Message &msg);

	/**
	 * Encodes a logon
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

} /* namespace */
} /* namespace Metal */
#endif /* prevent multiple includes */
