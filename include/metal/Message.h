/*
 * Message.h
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#ifndef METAL_MESSAGE_H_
#define METAL_MESSAGE_H_

#include <iostream>

namespace Metal {

class Message {
public:
	Message();
	virtual ~Message();

	inline const char* getData() { return data; };
	inline const size_t getLength() { return length; };
	inline void setLength( size_t length) { this->length = length; };

	/**
	 * Write a single character at given position
	 * @param position Where the character should be writted
	 * @param value Value to be written
	 */
	inline void set( int position, char value) { this->data[position] = value;};

	/**
	 * Write a complete string at given position
	 * @param position Where the string should be writted
	 * @param str String to be written
	 * @param maxLength maximum length to be copied from the string
	 */
	inline void set(int position, std::string str, int maxLength) {
		int remainder = str.length();
		if( maxLength < remainder) remainder = maxLength;
		std::strncpy( &this->data[position], str.c_str(), remainder);
	};

private:
	char data[2048];
	unsigned int length;
};

} /* namespace Metal */

#endif /* METAL_MESSAGE_H_ */
