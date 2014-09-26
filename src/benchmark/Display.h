#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display
{
public:
	Display();
	~Display();

	static void getCPUDescription(std::string &str);
	static void getOSDescription(std::string &str);
};

#endif //DISPLAY_H
