//============================================================================
// Name        : IConsole
// Author      : Riyufuchi
// Created on  : 13.10.2023
// Last Edit   : 20.11.2023
// Description : This a base class Classes working with console
//============================================================================

#ifndef SRC_INC_ICONSOLE_HPP_
#define SRC_INC_ICONSOLE_HPP_

#include <sstream>
#include "Colors.h"

namespace ConsoleUtils
{
class IConsole
{
public:
	virtual void writeText(const char* text) = 0;
	virtual void writeText(std::string text) = 0;
	virtual void writeText(Colors::Color color, std::string text) = 0;
	virtual void writeTextLine(Colors::Color color, std::string text) = 0;
	virtual void writeText(short int r, short int g, short int b, std::string text) = 0;
	virtual void writeTextLine(short int r, short int g, short int b, std::string text) = 0;
	// Virtual destructor in the base class
	virtual ~IConsole()
	{
	}
};
}
#endif /* CONSOLEUTILS_ICONSOLE_HPP_ */
