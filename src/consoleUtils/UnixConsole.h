//============================================================================
// Name        : UnixConsole
// Author      : Riyufuchi
// Created on  : 20.07.2020
// Last Edit   : 22.11.2022
// Description : This class contains methods for working with a Linux console
//============================================================================

#ifndef _UNIXCONSOLE_H_
#define _UNIXCONSOLE_H_
#include <iostream>
#include <sstream>

class UnixConsole
{
public:
	struct Color
	{
		short int red;
		short int blue;
		short int green;
	};
	UnixConsole();
	void writeText(const char* text);
	void writeText(std::string text);
	void writeText(Color color, const char* text);
	void writeText(int  r, int g, int b, const char* text);
	void setTextColor(Color color);
	Color newColor(short int r, short int g, short int b);
	~UnixConsole();
private:
	Color mainColor;
};
#endif
