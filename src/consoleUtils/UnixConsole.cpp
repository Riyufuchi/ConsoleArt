//============================================================================
// Name        : UnixConsole
// Author      : Riyufuchi
// Created on  : 20.07.2020
// Last Edit   : 06.03.2023
// Description : This class contains methods for working with a Linux console
//============================================================================

#include "UnixConsole.h"
using namespace ConsoleUtils;

UnixConsole::UnixConsole()
{
	mainColor.red = 5;
	mainColor.green = 195;
	mainColor.blue = 221;
}
//TODO: Find out most efficient method (printf, just cout, ostringstream)
void UnixConsole::writeText(short int r, short int g, short int b, const char* text)
{
	std::cout << "\e[38;2;" << r << ";" << g << ";" << b << "m" << text << "\e[m\n";
}
void UnixConsole::writeText(std::string text)
{
	std::ostringstream t;
	t << "\e[38;2;" << mainColor.red << ";" << mainColor.green << ";" << mainColor.blue << "m" << text << "\e[m\n";
	std::cout << t.str();
}
void UnixConsole::writeText(Color color, const char* text)
{
	writeText(color.red, color.green, color.blue, text);
}
void UnixConsole::writeText(const char* text)
{
	writeText(mainColor.red, mainColor.green, mainColor.blue, text);
}
void UnixConsole::setTextColor(Color color)
{
	mainColor = color;
}
UnixConsole::~UnixConsole()
{
}
