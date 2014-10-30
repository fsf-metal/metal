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
#ifndef CODEC_H
#define CODEC_H

#include <stdint.h>

#include <metal/metal.h>
#include <metal/Message.h>

namespace Metal {

class Codec
{
public:
	Codec();

	/**
	 * Find out message length from its wire representation.
	 * Will find out message length and copy data into msg bytes.
	 * @param data Byte array containing data
	 * @param size Number of bytes in array
	 * @return Message length or 0 if no message was found in data
	 */
	virtual int getMessageLength(char* data, int size){ return 0; };

	/**
	 * Decodes a 8 bits integer from a message
	 */
	inline void decode(const char * data, int position, int8_t &output) {
		output = (int8_t)data[position];
	}

	/**
	 * Decodes a 8 bits integer from a message
	 */
	inline void decode(const char * data, int position, uint8_t &output) {
		output = (uint8_t)data[position];
	}

	/**
	 * Decodes a 16 bits integer from a message in big endian format
	 */
	inline void decodeBE( const char * data, int position, int16_t &output) {
		output = ((int16_t)(data[position] & 0xFF)) << 8;
		output += (int16_t)(data[position+1] & 0xFF);
	}

	/**
	 * Decodes an unsigned 16 bits integer from a message in big endian format
	 */
	inline void decodeBE(const char * data, int position, uint16_t &output) {
		output  = ((uint16_t)(data[position] & 0xFF)) << 8;
		output +=  (uint16_t)(data[position + 1] & 0xFF);
	}

	/**
	 * Decodes a 32 bits integer from a message in big endian format
	 */
	inline void decodeBE( const char * data, int position, int32_t &output) {
		output  = ((int32_t)(data[position] & 0xFF)) << 24;
		output += ((int32_t)(data[position + 1] & 0xFF)) << 16;
		output += ((int32_t)(data[position + 2] & 0xFF)) << 8;
		output += ((int32_t)(data[position + 3] & 0xFF));
	}

	/**
	 * Decodes an unsigned 32 bits integer from a message in big endian format
	 */
	inline void decodeBE(const char * data, int position, uint32_t &output) {
		output  = ((uint32_t)(data[position] & 0xFF)) << 24;
		output += ((uint32_t)(data[position + 1] & 0xFF)) << 16;
		output += ((uint32_t)(data[position + 2] & 0xFF)) << 8;
		output += ((uint32_t)(data[position + 3] & 0xFF));
	}

	/**
	 * Decodes a 64 bits integer from a message in big endian format
	 */
	inline void decodeBE( const char * data, int position, int64_t &output) {
		output  = ((int64_t)(data[position] & 0xFF)) << 56;
		output += ((int64_t)(data[position + 1] & 0xFF)) << 48;
		output += ((int64_t)(data[position + 2] & 0xFF)) << 40;
		output += ((int64_t)(data[position + 3] & 0xFF)) << 32;
		output += ((int64_t)(data[position + 4] & 0xFF)) << 24;
		output += ((int64_t)(data[position + 5] & 0xFF)) << 16;
		output += ((int64_t)(data[position + 6] & 0xFF)) << 8;
		output += ((int64_t)(data[position + 7] & 0xFF));
	}

	/**
	 * Decodes a 64 bits integer from a message in big endian format
	 */
	inline void decodeBE( const char * data, int position, uint64_t &output) {
		output  = ((uint64_t)(data[position] & 0xFF)) << 56;
		output += ((uint64_t)(data[position + 1] & 0xFF)) << 48;
		output += ((uint64_t)(data[position + 2] & 0xFF)) << 40;
		output += ((uint64_t)(data[position + 3] & 0xFF)) << 32;
		output += ((uint64_t)(data[position + 4] & 0xFF)) << 24;
		output += ((uint64_t)(data[position + 5] & 0xFF)) << 16;
		output += ((uint64_t)(data[position + 6] & 0xFF)) << 8;
		output += ((uint64_t)(data[position + 7] & 0xFF));
	}

	/**
	 * Decodes a 16 bits integer from a message in little endian format
	 */
	inline void decodeLE( const char * data, int position, int16_t &output) {
		output  =  (int16_t)( data[position] & 0xFF);
		output += ((int16_t)( data[position + 1] & 0xFF)) << 8;
	}

	/**
	 * Decodes a 16 bits integer from a message in little endian format
	 */
	inline void decodeLE(const char * data, int position, uint16_t &output) {
		output  =  (uint16_t)(data[position] & 0xFF);
		output += ((uint16_t)(data[position + 1] & 0xFF)) << 8;
	}

	/**
	 * Decodes a 32 bits integer from a message in little endian format
	 */
	inline void decodeLE(const char * data, int position, int32_t &output) {
		output  =  (int32_t)(data[position] & 0xFF);
		output += ((int32_t)(data[position + 1] & 0xFF)) << 8;
		output += ((int32_t)(data[position + 2] & 0xFF)) << 16;
		output += ((int32_t)(data[position + 3] & 0xFF)) << 24;
	}

	/**
	 * Decodes an unsigned 32 bits integer from a message in little endian format
	 */
	inline void decodeLE(const char * data, int position, uint32_t &output) {
		output  =  (uint32_t)(data[position] & 0xFF);
		output += ((uint32_t)(data[position + 1] & 0xFF)) << 8;
		output += ((uint32_t)(data[position + 2] & 0xFF)) << 16;
		output += ((uint32_t)(data[position + 3] & 0xFF)) << 24;
	}

	/**
	 * Decodes a 64 bits integer from a message in little endian format
	 */
	inline void decodeLE(const char * data, int position, int64_t &output) {
		output  =  (int64_t)(data[position] & 0xFF);
		output += ((int64_t)(data[position + 1] & 0xFF)) << 8;
		output += ((int64_t)(data[position + 2] & 0xFF)) << 16;
		output += ((int64_t)(data[position + 3] & 0xFF)) << 24;
		output += ((int64_t)(data[position + 4] & 0xFF)) << 32;
		output += ((int64_t)(data[position + 5] & 0xFF)) << 40;
		output += ((int64_t)(data[position + 6] & 0xFF)) << 48;
		output += ((int64_t)(data[position + 7] & 0xFF)) << 56;
	}

	/**
	 * Decodes an unsigned 64 bits integer from a message in little endian format
	 */
	inline void decodeLE(const char * data, int position, uint64_t &output) {
		output  =  (uint64_t)(data[position]) & 0xFF;
		output += ((uint64_t)(data[position + 1] & 0xFF)) << 8;
		output += ((uint64_t)(data[position + 2] & 0xFF)) << 16;
		output += ((uint64_t)(data[position + 3] & 0xFF)) << 24;
		output += ((uint64_t)(data[position + 4] & 0xFF)) << 32;
		output += ((uint64_t)(data[position + 5] & 0xFF)) << 40;
		output += ((uint64_t)(data[position + 6] & 0xFF)) << 48;
		output += ((uint64_t)(data[position + 7] & 0xFF)) << 56;
	}

	/**
	 * Copies data into a string
	 */
	inline void decode(const char * data, int position, std::string &output, int maxLength) {
		output.assign( &data[position], maxLength);
	}

	/**
	 * Encode a string up to the given length.
	 * @param str String to be encoded
	 */
	inline void encode(const std::string &str, Message &msg, int position, int maxLength){
		msg.set(position, str, maxLength);
	};

	inline void encode(const int8_t &i, Message &msg, int position){
		msg.set(position, i);
	};

	inline void encodeLE(const int16_t &i, Message &msg, int position) {
		msg.set(  position, (char) (i & 0x00FF));
		msg.set(++position, (char)((i & 0xFF00) >> 8));
	};

	inline void encodeLE( const uint16_t &i, Message &msg, int position) {
		msg.set(  position, (char) (i & 0x00FF));
		msg.set(++position, (char)((i & 0xFF00) >> 8));
	}

	inline void encodeBE(const int16_t &i, Message &msg, int position) {
		msg.set(  position, ((i & 0xFF00) >> 8));
		msg.set(++position, (i & 0x00FF));
	};

	inline void encodeBE(const uint16_t &i, Message &msg, int position) {
		msg.set(  position, ((i & 0xFF00) >> 8));
		msg.set(++position, (i & 0x00FF));
	};

	// revised
	inline void encodeLE(const int32_t &i, Message &msg, int position) {
		msg.set(  position, (char)( i & 0x000000FF));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0xFF000000) >> 24));
	};

	inline void encodeLE(const uint32_t &i, Message &msg, int position) {
		msg.set(  position, (char)( i & 0x000000FF));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0xFF000000) >> 24));
	};

	inline void encodeBE(const int32_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF000000) >> 24));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char) (i & 0x000000FF));
	};

	inline void encodeBE(const uint32_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF000000) >> 24));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char) (i & 0x000000FF));
    }

	inline void encodeLE(const int64_t &i, Message &msg, int position){
		msg.set(  position, (char) (i & 0x00000000000000FF));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0xFF00000000000000) >> 56));
	};

	inline void encodeLE(const uint64_t &i, Message &msg, int position){
		msg.set(  position, (char) (i & 0x00000000000000FF));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0xFF00000000000000) >> 56));
	};

	inline void encodeBE(const int64_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF00000000000000) >> 56));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char) (i & 0x00000000000000FF));
	};

	inline void encodeBE(const uint64_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF00000000000000) >> 56));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char) (i & 0x00000000000000FF));
	};

	/**
	 * This method should be overriden for exchanges that require a heartbeat<br>
	 * @param msg Where encoded HeartBeat Message will be stored
	 */
	virtual void encodeHeartBeat(Message &msg){};

	/**
	 * This method should be overriden by exchanges that require a logon<br>
	 * @param msg Where encoded Logon Message will be stored
	 */
	virtual void encodeLogon(Message &msg){};

	static std::string Codec::formatHex(char * data, int length);

	virtual ~Codec();
};

}

#endif // CODEC_H
