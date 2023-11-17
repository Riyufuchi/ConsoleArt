//============================================================================
// Name        : IConsole
// Author      : Riyufuchi
// Created on  : 13.10.2023
// Last Edit   : 13.10.2023
// Description : This a base class Classes working with console
//============================================================================

#ifndef CONSOLEUTILS_ICONSOLE_HPP_
#define CONSOLEUTILS_ICONSOLE_HPP_

#include <sstream>

namespace ConsoleUtils
{
typedef struct Color // This way, there is no need to cast, because uint8_t would be treated as char not numerical value
{
	short int red;
	short int blue;
	short int green;
} tColor;
class IConsole
{
public:
	virtual void writeText(const char* text) = 0;
	virtual void writeText(std::string text) = 0;
	virtual void writeText(Color color, const char* text) = 0;
	virtual void writeText(short int r, short int g, short int b, const char* text) = 0;
	Color newColor(short int r, short int g, short int b)
	{
		Color color;
		color.red = r;
		color.green = g;
		color.blue = b;
		return color;
	}
	// Virtual destructor in the base class
	virtual ~IConsole()
	{
	}
};
}
#endif /* CONSOLEUTILS_ICONSOLE_HPP_ */
