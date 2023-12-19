//============================================================================
// Name        : UnixConsole
// Author      : Riyufuchi
// Created on  : 20.07.2020
// Last Edit   : 08.12.2023
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
	void setDefaultTextColor(Color color);
	void setTextColor(Color color) override;
	// Getters
	Color getDefaultTextColor();
	// Write methods
	void out(const char* text) override;
	void out(std::string text) override;
	void out(Color color, std::string text) override;
	void out(short int r, short int g, short int b, std::string text) override;
	void err(std::string text) override;
	void err(Color color, std::string text) override;
	void err(short int r, short int g, short int b, std::string text) override;
	~UnixConsole();
private:
	Color mainColor;
};
}
#endif
