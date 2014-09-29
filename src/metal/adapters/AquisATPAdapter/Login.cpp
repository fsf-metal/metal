/*
 * Login.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: jc
 */

#include "Login.h"

namespace Metal {
namespace Aquis {

Login::Login() {
	// Version 1.3 = 0x0103
	this->protocolVersion = 0x0103;
	this->atqSeqNo = 1;
}

Login::~Login() {
	// TODO Auto-generated destructor stub
}

} /* namespace Aquis */
} /* namespace Metal */
