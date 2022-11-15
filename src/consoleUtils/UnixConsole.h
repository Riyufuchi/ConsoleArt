//============================================================================
// Name        : UnixConsole
// Author      : Riyufuchi
// Created on  : 20.07.2020
// Last Edit   : 15.11.2022
// Description : This class contains methods for working with a Linux console
//============================================================================

#ifndef  _UNXCONSOLE_H_
#define _UNIXCONSOLE_H_
#include <iostream>
#include <sstream>

class UnixConsole
{
private:
	struct Color
	{
		short int red;
		short int blue;
		short int green;
	};
	Color mainColor;
public:
	UnixConsole();
	void setMainTextColor(Color a);
	Color setColor(short int r, short int g, short int b);
	void setColorText(Color a, const char* text);
	void writeText(std::string text);
	void setColorText(int  r, int g, int b, const char* text);
	~UnixConsole();
};
#endif
