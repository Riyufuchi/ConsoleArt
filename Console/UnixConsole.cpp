#include "UnixConsole.h"
/*
* Copyright Header
*
* Created On: 20.07.2020
* Last Edit: 25.10.2021
* Created By: Riyufuchi
*
*/
UnixConsole::UnixConsole()
{
	/*
	mainColor.red = 255;
	mainColor.green = 105;
	mainColor.blue = 180;
	*/
	mainColor.red = 160;
	mainColor.green = 0;
	mainColor.blue = 255;
}
void UnixConsole::setColorText(int r, int g, int b, const char * text)
{
	std::ostringstream t;
	t << "\e[38;2;" << r << ";" << g << ";" << b << "m" << text << "\e[m";
	//std::string str(t.str());
	std::cout << t.str() << std::endl;
}
void UnixConsole::setColorText(Color a, const char * text)
{
	std::ostringstream t;
	t << "\e[38;2;" << a.red << ";" << a.green << ";" << a.blue << "m" << text << "\e[m";
	//std::string str(t.str());
	std::cout << t.str() << std::endl;
}
void UnixConsole::writeText(std::string text)
{
	std::ostringstream t;
	t << "\e[38;2;" << mainColor.red << ";" << mainColor.green << ";" << mainColor.blue << "m" << text << "\e[m";
	//std::string str(t.str());
	std::cout << t.str() << std::endl;
}
void UnixConsole::setMainTextColor(UnixConsole::Color a)
{
	mainColor = a;
}
UnixConsole::Color UnixConsole::setColor(int r, int g, int b)
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
