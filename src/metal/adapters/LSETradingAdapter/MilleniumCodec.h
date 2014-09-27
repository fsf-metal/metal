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

namespace Metal {
namespace LSE {

class MilleniumCodec : public Codec {
public:
	MilleniumCodec();
	virtual ~MilleniumCodec();

	static void encode( const OrderCancelRequest &, Message &);
	static void encode( const NewOrder &, Message &);
	inline static void encode(const int16_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };
	inline static void encode(const int32_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };
	inline static void encode(const int64_t &i, Message &msg, int position) { encodeLittleEndian(i, msg, position); };

	inline static void encodeHeader( Message &msg, int16_t length, char type);
};

} /* namespace LSE */
} /* namespace Metal */
#endif /* METAL_LSE_LSEMESSAGEENCODER_H_ */
