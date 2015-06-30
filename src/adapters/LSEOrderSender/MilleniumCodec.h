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

#ifndef METAL_LSE_MILLENIUMCODEC_H
#define METAL_LSE_MILLENIUMCODEC_H

#include <metal/Message.h>
#include <metal/Codec.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"
#include "Logon.h"
#include "ExecutionReport.h"

namespace Metal {
namespace LSE {

	/**
	 * This class knows all about LSE specific format.<br>
	 * It is used to code/decode LSE Messages representation into/from their wire format.<br>
	 * It is worth noticing that it does not know how to process generic messages.
	 */
	class MilleniumCodec : public Codec {
	public:
		MilleniumCodec();
		virtual ~MilleniumCodec();

		/**
		 * Minimum message length to retreive header
		 */
		static const int HEADER_LENGTH = 4;

		/**
		 * Read inbound execution report
		 */
		void decode(const char * data, ExecutionReport &er);

		//-------------------------------------------
		// Few handy aliases, LSE Uses little endian
		//-------------------------------------------
		inline void decode(const char * data, int position, int16_t &output) { decodeLE(data, position, output); }
		inline void decode(const char * data, int position, uint16_t &output) { decodeLE(data, position, output); }
		inline void decode(const char * data, int position, int32_t &output) { decodeLE(data, position, output); }
		inline void decode(const char * data, int position, uint32_t &output) { decodeLE(data, position, output); }
		inline void decode(const char * data, int position, int64_t &output) { decodeLE(data, position, output); }
		inline void decode(const char * data, int position, uint64_t &output) { decodeLE(data, position, output); }

		//------------------
		// LSE Messages
		//------------------
		/**
		 * Encode a cancel request
		 * @param ocr The Order Cancel Request representation
		 * @param msg The destination message
		 */
		void encode(const OrderCancelRequest & ocr, Message &msg);

		/**
		 * Encode a new order
		 * @param no The New Order representation
		 * @param msg The destination message
		 */
		void encode(const NewOrder &no, Message &msg);

		/**
		 * Encode a logon
		 * @param logon Logon representation. Must be constructed with all values
		 * @param msg The destination message
		 */
		void encode(const Logon &logon, Message &msg);

		//------------------------------------------------------------------------------------
		// Fields
		// We are relying on Codec:: little endian methods, just wrapping them for ease of use
		//------------------------------------------------------------------------------------
		inline void encode(const int16_t &i, Message &msg, int position) { encodeLE(i, msg, position); };
		inline void encode(const int32_t &i, Message &msg, int position) { encodeLE(i, msg, position); };
		inline void encode(const int64_t &i, Message &msg, int position) { encodeLE(i, msg, position); };

		/**
		 * LSE heartbeat encoding
		 * @see Codec#encodeHeader
		 */
		inline void encodeHeader(Message &msg, int16_t length, char type);
		void encodeHeartBeat(Message &msg);

	};


} /* namespace LSE */
} /* namespace Metal */
#endif /* METAL_LSE_MILLENIUMCODEC_H_ */
