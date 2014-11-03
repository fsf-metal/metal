#ifndef METAL_LSE_LOGON_H
#define METAL_LSE_LOGON_H

#include <string>

#include <metal/Message.h>

namespace Metal {
namespace LSE {

class Logon : public Message {
public:
	Logon(std::string userNameParam, std::string passwordParam, std::string newPasswordParam = NULL);
	~Logon(){};

	std::string userName;
	std::string password;
	std::string newPassword;

protected:

};

}
}

#endif //  METAL_LSE_LOGON_H
