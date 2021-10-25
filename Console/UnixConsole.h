#ifndef  _UNXCONSOLE_H_
#define _UNIXCONSOLE_H_
#include <iostream>
#include <sstream>

/*
* Copyright Header
*
* Created On: 20.07.2020
* Last Edit: 25.10.2021
* Created By: Riyufuchi
*
*/

class UnixConsole
{
private:
	struct Color
	{
		int red;
		int blue;
		int green;
	};
	Color mainColor;
public:
	UnixConsole();
	void setMainTextColor(Color a);
	Color setColor(int  r, int g, int b);
	void setColorText(Color a, const char* text);
	void writeText(std::string text);
	void setColorText(int  r, int g, int b, const char* text);
	~UnixConsole();
};
#endif
