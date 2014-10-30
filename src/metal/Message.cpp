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
#include <cstring>
#include <metal/Message.h>

namespace Metal {

Message::Message() : length(0) {
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

void Message::reset() {
	memset(this->data, 0, Message::MAX_LENGTH);
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
