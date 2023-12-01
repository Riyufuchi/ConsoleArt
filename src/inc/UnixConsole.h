//============================================================================
// Name        : UnixConsole
// Author      : Riyufuchi
// Created on  : 20.07.2020
// Last Edit   : 28.11.2023
// Description : This class contains methods for working with a Linux console
//============================================================================

#ifndef _UNIXCONSOLE_H_
#define _UNIXCONSOLE_H_

#include <iostream>
#include <sstream>

#include "IConsole.hpp"

namespace ConsoleUtils
{
class UnixConsole : public IConsole
{
public:
	UnixConsole();
	void resetTextColor() override;
	// Setters
	void setDefaultTextColor(Colors::Color color);
	void setTextColor(Colors::Color color) override;
	// Getters
	Colors::Color getDefaultTextColor();
	// Write methods
	void out(const char* text) override;
	void out(std::string text) override;
	void out(Colors::Color color, std::string text) override;
	void out(short int r, short int g, short int b, std::string text) override;
	~UnixConsole();
private:
	Colors::Color mainColor;
};
}
#endif
