#ifndef CODEC_H
#define CODEC_H

#include <stdint.h>
#include <metal/Message.h>

namespace Metal {

class Codec
{
public:
	Codec();

	inline void encode(const std::string &str, Message &msg, int position, int maxLength){
		msg.set(position, str, maxLength);
	};

	inline void encode(const int8_t &i, Message &msg, int position){
		msg.set(position, i);
	};

	inline void encodeLittleEndian(const int16_t &i, Message &msg, int position) {
		msg.set(  position, (char)((i & 0xFF00) >> 8));
		msg.set(++position, (char) (i & 0x00FF));
	};

	inline void encodeLittleEndian( const uint16_t &i, Message &msg, int position) {
		msg.set(  position, (char)((i & 0xFF00) >> 8));
		msg.set(++position, (char) (i & 0x00FF));
	}

	inline void encodeBigEndian(const int16_t &i, Message &msg, int position) {
		msg.set(  position, (i & 0x00FF));
		msg.set(++position, ((i & 0xFF00) >> 8));
	};

	inline void encodeLittleEndian(const int32_t &i, Message &msg, int position) {
		msg.set(  position, (char)((i & 0xFF000000) >> 24));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char) (i & 0x000000FF));
	};

	inline void encodeLittleEndian(const uint32_t &i, Message &msg, int position) {
		msg.set(  position, (char)((i & 0xFF000000) >> 24));
		msg.set(++position, (char)((i & 0x00FF0000) >> 16));
		msg.set(++position, (char)((i & 0x0000FF00) >> 8));
		msg.set(++position, (char) (i & 0x000000FF));
	};

	inline void encodeBigEndian(const int32_t &i, Message &msg, int position){
		msg.set(  position, (i & 0x000000FF));
		msg.set(++position, ((i & 0x0000FF00) >> 8));
		msg.set(++position, ((i & 0x00FF0000) >> 16));
		msg.set(++position, ((i & 0xFF000000) >> 24));
	};

	inline void encodeLittleEndian(const int64_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF00000000000000) >> 56));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char) (i & 0x00000000000000FF));
	};

	inline void encodeLittleEndian(const uint64_t &i, Message &msg, int position){
		msg.set(  position, (char)((i & 0xFF00000000000000) >> 56));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char) (i & 0x00000000000000FF));
	};

	inline void encodeBigEndian(const int64_t &i, Message &msg, int position){
		msg.set(  position, (char) (i & 0x00000000000000FF));
		msg.set(++position, (char)((i & 0x000000000000FF00) >> 8));
		msg.set(++position, (char)((i & 0x0000000000FF0000) >> 16));
		msg.set(++position, (char)((i & 0x00000000FF000000) >> 24));
		msg.set(++position, (char)((i & 0x000000FF00000000) >> 32));
		msg.set(++position, (char)((i & 0x0000FF0000000000) >> 40));
		msg.set(++position, (char)((i & 0x00FF000000000000) >> 48));
		msg.set(++position, (char)((i & 0xFF00000000000000) >> 56));
	};

	virtual ~Codec();
};

}

#endif // CODEC_H
