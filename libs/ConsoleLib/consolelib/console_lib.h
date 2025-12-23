//==============================================================================
// File       : ConsoleLib.h
// Author     : Riyufuchi
// Created on : Mar 27, 2024
// Last edit  : Dec 22, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consolelib
//==============================================================================

#ifndef _CONSOLE_LIB_LIBRARY_H_
#define _CONSOLE_LIB_LIBRARY_H_

#include <iostream>
#include <string>
#include <format>

#define _VERSION "7.0"

namespace consolelib
{
class ConsoleLib
{
public:
	static constexpr const char* VERSION = _VERSION;
	ConsoleLib() = default;
	~ConsoleLib() = default;;
	static std::string aboutLibrary();
};
}
#endif
