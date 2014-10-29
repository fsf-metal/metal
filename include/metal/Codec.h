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
#include <metal/Message.h>

namespace Metal {

class Codec
{
public:
	Codec();

	/**
	 * Decode a message from its wire representation
	 * @return Message length or 0 if no message was found in data
	 */
	virtual int decode(char* data, int size, Message &msg) = 0;

	inline void encode(const std::string &str, Message &msg, int position, int maxLength){
		msg.set(position, str, maxLength);
	};

	inline void encode(const int8_t &i, Message &msg, int position){
		msg.set(position, i);
	};

	inline void encodeLittleEndian(const int16_t &i, Message &msg, int position) {
		msg.set(  position, (char) (i & 0x00FF));
		msg.set(++position, (char)((i & 0xFF00) >> 8));
	};

	inline void encodeLittleEndian( const uint16_t &i, Message &msg, int position) {
		msg.set(  position, (char) (i & 0x00FF));
		msg.set(++position, (char)((i & 0xFF00) >> 8));
	}

	inline void encodeBigEndian(const int16_t &i, Message &msg, int position) {
		msg.set(  position, ((i & 0xFF00) >> 8));
		msg.set(++position, (i & 0x00FF));
	};

	inline void encodeBigEndian(const uint16_t &i, Message &msg, int position) {
		msg.set(  position, ((i & 0xFF00) >> 8));
		msg.set(++position, (i & 0x00FF));
	};

	// revised
	inline void encodeLittleEndian(const int32_t &i, Message &msg, int position) {
		msg.set(  position, (char)( i & 0x000000FF));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0xFF000000) >> 24));
	};

	inline void encodeLittleEndian(const uint32_t &i, Message &msg, int position) {
		msg.set(  position, (char)( i & 0x000000FF));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0xFF000000) >> 24));
	};

	inline void encodeBigEndian(const int32_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF000000) >> 24));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char) (i & 0x000000FF));
	};

	inline void encodeBigEndian(const uint32_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF000000) >> 24));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char) (i & 0x000000FF));
    }

	inline void encodeLittleEndian(const int64_t &i, Message &msg, int position){
		msg.set(  position, (char) (i & 0x00000000000000FF));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0xFF00000000000000) >> 56));
	};

	inline void encodeLittleEndian(const uint64_t &i, Message &msg, int position){
		msg.set(  position, (char) (i & 0x00000000000000FF));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0xFF00000000000000) >> 56));
	};

	inline void encodeBigEndian(const int64_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF00000000000000) >> 56));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char) (i & 0x00000000000000FF));
	};

	inline void encodeBigEndian(const uint64_t &i, Message &msg, int position){
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
	 * This method should be overriden by subclasses<br>
	 * @param msg Where encoded HeartBeat Message will be stored
	 */
	virtual void encodeHeartBeat(Message &msg){};

	/**
	 * This method should be overriden by subclasses<br>
	 * @param msg Where encoded Logon Message will be stored
	 */
	virtual void encodeLogon(Message &msg){};


	virtual ~Codec();
};

}

#endif // CODEC_H
