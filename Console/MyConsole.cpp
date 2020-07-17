#include "MyConsole.h"
MyConsole::MyConsole()
{
	console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//DWORD d = ff69b4;
	SetTextColor((HDC)console, RGB(255, 105, 180));
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
	//SetTextColor(GetDC((HWND)console), RGB(255, 105, 180));
	DWORD bytesWritten = 0;
	while (1)
	{

		screen[screenWidth * screenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(console, (LPCSTR)screen, screenWidth * screenHeight, { 0, 0 }, &bytesWritten);
	}
}
void MyConsole::setBGColor(int r, int g, int b)
{
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);
	info.ColorTable[1] = RGB(r, g, b);
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