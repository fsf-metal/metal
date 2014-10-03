#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

using namespace std;

class Display
{
public:
	Display();
	~Display();

	static string formatWithCommas(long value);
	static void getCPUDescription(string &str);
	static void getOSDescription(string &str);
};

#endif //DISPLAY_H
