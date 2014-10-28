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


#ifndef __METAL_EXCEPTIONS_H_
#define __METAL_EXCEPTIONS_H_

#include <exception>
#include <string>

namespace Metal {

class MetalException : public std::exception {
	private:
		std::string message_;
	public:
		MetalException(const std::string& message) : message_(message) {};
		virtual const char* what() const throw() {
			return message_.c_str();
		}

};

class MappingException : public MetalException {
public:
	MappingException(const std::string& message) : MetalException(message) {};
};

class MissingImplementationException : public MetalException {
public:
	MissingImplementationException(const std::string& message) : MetalException(message) {};
};

class SendMessageException : public MetalException {
public:
	SendMessageException(const std::string& message) : MetalException(message) {};
};

} /* namespace Metal */
#endif /* __METAL_EXCEPTIONS_H_ */
