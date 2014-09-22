/*
 * MappingException.h
 *
 *  Created on: Sep 15, 2014
 *      Author: jc
 */

#ifndef __METALMAPPINGEXCEPTION_H_
#define __METALMAPPINGEXCEPTION_H_

#include <exception>
#include <string>

namespace Metal {

class MappingException: public std::exception {
private:
    std::string message_;
public:
    MappingException(const std::string& message);
    virtual const char* what() const throw() {
        return message_.c_str();
    }
};

} /* namespace Metal */
#endif /* __METALMAPPINGEXCEPTION_H_ */
