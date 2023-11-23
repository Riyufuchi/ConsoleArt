//==============================================================================
// File       : AsciiPrinter.h
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Nov 22, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGEUTILS_ASCIIPRINTER_H_
#define IMAGEUTILS_ASCIIPRINTER_H_

#include <string>
#include <codecvt>
#include <iostream>
#include <locale>

#include "../imageUtils/AsciiConverter.h"
#include "../inc/IConsole.hpp"

namespace ConsoleArt
{
class AsciiPrinter
{
private:
	ImageUtils::AsciiConverter& asciiCon;
	ConsoleUtils::IConsole& console;
public:
	AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console);
	~AsciiPrinter();
	void printClassic();
	void printPixelColored();
	void printCharColored();

};
} /* namespace Images */
#endif /* IMAGEUTILS_ASCIIPRINTER_H_ */
