#include "MyUnixConsole.h"
/*
* Copyright Header
*
* Created On: 20.07.2020
* Last Edit: 20.07.2020
* Created By: Riyufuchi
*
*/
MyUnixConsole::MyUnixConsole()
{
	mainColor.red = 255;
	mainColor.green = 105;
	mainColor.blue = 180;
}
void MyUnixConsole::setColorText(int r, int g, int b, const char * text)
{
	const char* t = '\e[0m' + '\e' + '[38' + ';2;' + r + ';' + g  + ';' + b + 'm' + text + '\e[m';
	printf(t + '\n');
}
void MyUnixConsole::setColorText(Color a, const char * text)
{
	const char* t = '\e[0m' + '\e' + '[38' + ';2;' + a.red + ';' + a.green + ';' + a.blue + 'm' + text + '\e[m';
	printf(t + '\n');
}
void MyUnixConsole::writeText(const char * text)
{
	const char* t = '\e[0m' + '\e' + '[38' + ';2;' + mainColor.red + ';' + mainColor.green + ';' + mainColor.blue + 'm' + text + '\e[m';
	printf(t);
}
void MyUnixConsole::setMainTextColor(MyUnixConsole::Color a)
{
	mainColor = a;
}
MyUnixConsole::Color MyUnixConsole::setColor(int r, int g, int b)
{
	Color a;
	a.red = r;
	a.green = g;
	a.blue = b;
	return a;
}
MyUnixConsole::~MyUnixConsole()
{
}