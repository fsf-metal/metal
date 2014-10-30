/*
 * Message.h
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#ifndef METAL_MESSAGE_H_
#define METAL_MESSAGE_H_

#include <iostream>
#include <string.h>

namespace Metal {

/**
 * This class purpose is message data storage. It does not contain functional information about content.
 */
class Message {
public:
	static const int MAX_LENGTH = 4096;
	Message();
	virtual ~Message();

	inline char* getData() { return data; };
	inline const size_t getLength() { return length; };
	inline void setLength( size_t length) { this->length = length; };

    /**
     * Read character at given position. Position must be valid
     * @param position A valid position (< length)
     */
    inline char get(int position) { return this->data[position]; }

	void reset();

	/**
	 * Write a single character at given position.
	 * @param position Where the character should be written. Must be valid (<length)
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
		int remainder = maxLength - str.length();
		if ( remainder <= 0) {
			strncpy(&this->data[position], str.c_str(), maxLength);
		} else {
			strcpy(&this->data[position], str.c_str());
			memset(&this->data[position + str.length()], 0, remainder);
		}
	};

private:
	char data[ MAX_LENGTH];
	unsigned int length;
};

} /* namespace Metal */

#endif /* METAL_MESSAGE_H_ */
