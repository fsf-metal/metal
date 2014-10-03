/*
 * Message.cpp
 *
 *  Created on: Sep 22, 2014
 *      Author: jc
 */

#include <cstring>
#include <metal/Message.h>

namespace Metal {

Message::Message() {
	// TODO Auto-generated constructor stub

}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

/*
void Message::set( int position, char value) {
	this->data[position] = value;
}

void Message::set( int position, std::string str, int maxLength) {
	int remainder = str.length();
	if( maxLength < remainder) remainder = maxLength;
	std::strncpy( &this->data[position], str.c_str(), remainder);
}
*/

} /* namespace Metal */
