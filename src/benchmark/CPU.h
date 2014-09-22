#ifndef CPU_H
#define CPU_H

#include <string>

class CPU
{
public:
	CPU();
	~CPU();

	static void getDetails(std::string &str);
};

#endif //CPU_H