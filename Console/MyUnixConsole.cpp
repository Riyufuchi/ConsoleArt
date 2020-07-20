#include "MyConsole.h"
/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 18.07.2020
* Created By: Riyufuchi
*
*/
MyConsole::MyConsole()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);
	info.ColorTable[1] = RGB(255, 105, 180); //HotPink
	SetConsoleScreenBufferInfoEx(hConsole, &info);
}
MyConsole::MyConsole(int width, int height)
{
	//Create Screen Buffer
	screenWidth = width;
	screenHeight = height;
	screen = new wchar_t[screenWidth*screenHeight];
	console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
}
void MyConsole::start()
{
	DWORD bytesWritten = 0;
	while (1)
	{

		screen[screenWidth * screenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(console, (LPCSTR)screen, screenWidth * screenHeight, { 0, 0 }, &bytesWritten);
	}
}
void MyConsole::setBGColor(int r, int g, int b)
{

}
void MyConsole::setTextColor(MyConsole::COLORS color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void MyConsole::test()
{
	std::cout << "Test" << std::endl;
}
MyConsole::~MyConsole()
{
}