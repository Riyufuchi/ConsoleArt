#ifndef  _MYCONSOLE_H_
#define _MYCONSOLE_H_
#include <iostream>
//#include <Windows.h>

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 18.07.2020
* Created By: Riyufuchi
*
*/

using namespace std;
class MyConsole
{
private:
	int screenWidth;
	int screenHeight;
	wchar_t *screen;
	std::wstring name;
	HANDLE console; // @suppress("Type cannot be resolved")
public:
	enum COLORS
	{
		HOT_PINK = 1,
	};
	MyConsole(int width, int height);
	MyConsole();
	void test();
	void start();
	void setTextColor(COLORS);
	void setBGColor(int  r, int g, int b);
	~MyConsole();
};
#endif
