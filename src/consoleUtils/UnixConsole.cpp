//============================================================================
// Name        : UnixConsole
// Author      : Riyufuchi
// Created on  : 20.07.2020
// Last Edit   : 22.11.2022
// Description : This class contains methods for working with a Linux console
//============================================================================

#include "UnixConsole.h"

UnixConsole::UnixConsole()
{
	mainColor.red = 5;
	mainColor.green = 195;
	mainColor.blue = 221;
}
void UnixConsole::writeText(int r, int g, int b, const char* text)
{
	std::ostringstream t;
	t << "\e[38;2;" << r << ";" << g << ";" << b << "m" << text << "\e[m";
	std::cout << t.str() << std::endl;
}
void UnixConsole::writeText(std::string text)
{
	std::ostringstream t;
	t << "\e[38;2;" << mainColor.red << ";" << mainColor.green << ";" << mainColor.blue << "m" << text << "\e[m";
	std::cout << t.str() << std::endl;
}
void UnixConsole::writeText(Color c, const char* text)
{
	writeText(c.red, c.green, c.blue, text);
}
void UnixConsole::writeText(const char* text)
{
	writeText(mainColor.red, mainColor.green, mainColor.blue, text);
}
void UnixConsole::setMainTextColor(Color a)
{
	mainColor = a;
}
UnixConsole::Color UnixConsole::setColor(short int r, short int g, short int b)
{
	Color a;
	a.red = r;
	a.green = g;
	a.blue = b;
	return a;
}
UnixConsole::~UnixConsole()
{
}
