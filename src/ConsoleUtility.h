#ifndef  _CONSOLEUTILITY_H_
#define _CONSOLEUTILITY_H_

#include <string>
#include <iostream>

/* Copyright Header
* Created On: 27.10.2021
* Last Edit: 08.11.2022
* Created By: Riyufuchi
*/

class ConsoleUtility
{
private:

public:
	ConsoleUtility();
	static bool repeat();
	static bool yesNo(const char* text);
	static int getIntSafe();
	static int getIntSafe(int min, int max);
	static void header(std::string);
	~ConsoleUtility();
};
#endif
