#ifndef  _MYCONSOLE_H_
#define _MYCONSOLE_H_
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>
using namespace std;
class MyConsole
{
private:
	int screenWidth;
	int screenHeight;
	std::wstring name;
	HANDLE console;
public:
	enum COLORS
	{
		D_BLUE = 1,
		D_GREEN = 2,
		D_PINK = 5,
		L_PINK = 13
	};
	MyConsole(int width, int height, int fontW, int fontH);
	void test();
	void setTextColor(COLORS);
	void setRGBTextColor(int  r, int g, int b);
	~MyConsole();
};
#endif