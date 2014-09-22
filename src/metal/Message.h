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
	inline void set( int position, char value) { this->data[position] = value;};
	inline void set( int position, std::string str, int maxLength) {
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
