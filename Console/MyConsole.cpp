#include "MyConsole.h"
MyConsole::MyConsole(int width, int height, int fontW, int fontH)
{
	//Create Screen Buffer
	screenWidth = width;
	screenHeight = height;
	wchar_t *screen = new wchar_t[screenWidth*screenHeight];
	console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	DWORD bytesWritten = 0;
	screen[screenWidth * screenHeight - 1] = '\0';
	WriteConsoleOutputCharacter(console, (LPCSTR)screen, screenWidth * screenHeight, { 0, 0}, &bytesWritten);
}
void MyConsole::setRGBTextColor(int r, int g, int b)
{
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);
	info.ColorTable[0] = RGB(r, g, b);
	SetConsoleScreenBufferInfoEx(hConsole, &info);
}
void MyConsole::setTextColor(MyConsole::COLORS color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void MyConsole::test()
{
	std::cout << "Test" << std::endl;
	/*
	for (int i = 0; i < 256; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		std::cout << "Test = %d\n" << i << std::endl;
	}
	*/
}
MyConsole::~MyConsole()
{
}