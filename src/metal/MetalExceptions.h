/*
 * MappingException.h
 *
 *  Created on: Sep 15, 2014
 *      Author: jc
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
class SendMessageException : public MetalException {
public:
	SendMessageException(const std::string& message) : MetalException(message) {};
};

} /* namespace Metal */
#endif /* __METAL_EXCEPTIONS_H_ */
