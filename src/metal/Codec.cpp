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
#include <metal/Codec.h>

using namespace std;

namespace Metal {

Codec::Codec()
{
}


Codec::~Codec()
{
}


std::string Codec::formatHex(char * data, int length) {
	std::stringstream ss;

	for (int index = 0; index < length; ++index) {
		ss << uppercase << setfill('0') << setw(2) << hex << (data[index] & 0xFF) << " ";
		if (index % 16 == 15) ss << endl;
	}
	return ss.str();
}


}
