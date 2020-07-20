#ifndef  _MYUNXCONSOLE_H_
#define _MYUNIXCONSOLE_H_
#include <iostream>

/*
* Copyright Header
*
* Created On: 20.07.2020
* Last Edit: 20.07.2020
* Created By: Riyufuchi
*
*/

using namespace std;
class MyUnixConsole
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
	MyUnixConsole();
	void setMainTextColor(Color a);
	Color setColor(int  r, int g, int b);
	void setColorText(Color a, const char* text);
	void writeText(const char * text);
	void setColorText(int  r, int g, int b, const char* text);
	~MyUnixConsole();
};
#endif