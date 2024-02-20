//============================================================================
// Name        : IConsole
// Author      : Riyufuchi
// Created on  : 13.10.2023
// Last Edit   : 20.02.2024
// Description : This a base class Classes working with console
//============================================================================

#ifndef SRC_INC_ICONSOLE_HPP_
#define SRC_INC_ICONSOLE_HPP_

#include <sstream>

#include "ColorUtils.h"

namespace ConsoleUtils
{
class IConsole
{
public:
	virtual void resetTextColor() = 0;
	virtual void defaultTextColor() = 0;
	// Getters
	virtual Color getDefaultTextColor()
	{
		return Color{211, 215, 207};
	}
	// Setters
	virtual void setTextColor(Color color) = 0;
	virtual void setDefaultTextColor(Color color) = 0;
	// Write methods
	virtual void out(const char* text) = 0;
	virtual void out(std::string text) = 0;
	virtual void out(Color color, std::string text) = 0;
	virtual void out(short int r, short int g, short int b, std::string text) = 0;
	virtual void err(std::string text) = 0;
	virtual void err(Color color, std::string text) = 0;
	virtual void err(short int r, short int g, short int b, std::string text) = 0;
	// Virtual destructor in the base class
	virtual ~IConsole()
	{
	}
};
}
#endif /* CONSOLEUTILS_ICONSOLE_HPP_ */
