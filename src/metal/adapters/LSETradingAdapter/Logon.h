#ifndef METAL_LSE_LOGON_H
#define METAL_LSE_LOGON_H

#include <string>

namespace Metal {
namespace LSE {
class Logon
{
public:
	Logon(std::string userNameParam, std::string passwordParam, std::string newPasswordParam) : userName(userNameParam), password(passwordParam), newPassword(newPasswordParam){};
	~Logon();

public:
	std::string userName;
	std::string password;
	std::string newPassword;

};

}
}

#endif //  METAL_LSE_LOGON_H