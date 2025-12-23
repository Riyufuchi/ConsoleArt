//==============================================================================
// File       : ConsoleArtLib.h
// Author     : Riyufuchi
// Created on : Dec 19, 2025
// Last edit  : Dec 19, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consoleartlib
//==============================================================================

#ifndef _CONSOLE_ART_LIB_LIBRARY_H_
#define _CONSOLE_ART_LIB_LIBRARY_H_

#include <iostream>
#include <string>
#include <format>

#define _VERSION "1.3"
#define _COPYRIGHT_HEADER "Riyufuchi (c) 2025"

namespace consoleartlib
{
class ConsoleArtLib
{
public:
	static constexpr const char* VERSION = _VERSION;
	ConsoleArtLib();
	~ConsoleArtLib();
	static std::string aboutLibrary();
};
} /* namespace */
#endif /* _CONSOLE_ART_LIB_LIBRARY_H_ */
