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
	wchar_t *screen;
	std::wstring name;
	HANDLE console;
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