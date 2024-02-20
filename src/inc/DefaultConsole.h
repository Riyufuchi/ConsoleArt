//==============================================================================
// File       : DefaultConsole.h
// Author     : Riyufuchi
// Created on : Feb 19, 2024
// Last edit  : Feb 19, 2024
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleLib
//==============================================================================

#ifndef SRC_INC_DEFAULTCONSOLE_H_
#define SRC_INC_DEFAULTCONSOLE_H_

#include <iostream>
#include <sstream>

#include "IConsole.hpp"

namespace ConsoleUtils
{
class DefaultConsole : public IConsole
{
private:
public:
	DefaultConsole();
	void resetTextColor() override;
	void defaultTextColor() override;
	// Setters
	void setDefaultTextColor(Color color) override;
	void setTextColor(Color color) override;
	// Write methods
	void out(const char* text) override;
	void out(std::string text) override;
	void out(Color color, std::string text) override;
	void out(short int r, short int g, short int b, std::string text) override;
	void err(std::string text) override;
	void err(Color color, std::string text) override;
	void err(short int r, short int g, short int b, std::string text) override;
	~DefaultConsole();
};
}
#endif /* SRC_INC_DEFAULTCONSOLE_H_ */
