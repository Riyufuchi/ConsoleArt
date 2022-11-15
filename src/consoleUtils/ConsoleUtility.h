//============================================================================
// Name        : ConsoleUtility
// Author      : Riyufuchi
// Created on  : 27.10.2021
// Last Edit   : 15.11.2022
// Description : This class provide functionality for basic console IO
//============================================================================

#ifndef _CONSOLEUTILITY_H_
#define _CONSOLEUTILITY_H_

#include <string.h>
#include <iostream>

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
	static int basicMenu(int lenght, const char* menu[]);
	~ConsoleUtility();
};
#endif
