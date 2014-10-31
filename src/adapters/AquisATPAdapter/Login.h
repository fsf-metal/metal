/*
 * Login.h
 *
 *  Created on: Sep 29, 2014
 *      Author: jc
 */

#ifndef LOGIN_H_
#define LOGIN_H_

#include <string>
#include "AquisTypes.h"

namespace Metal {
namespace Aquis {

class Login {
public:
	Login();
	virtual ~Login();

	ProtocolVersion protocolVersion;
	std::string senderId;
	std::string password;
	InactivityTimeout inactivityTimeout;
	ATPSeqNo atqSeqNo;

};

} /* namespace Aquis */
} /* namespace Metal */
#endif /* LOGIN_H_ */
