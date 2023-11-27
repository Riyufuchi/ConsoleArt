//==============================================================================
// File       : AsciiPrinter.h
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : 23.11.2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGEUTILS_ASCIIPRINTER_H_
#define IMAGEUTILS_ASCIIPRINTER_H_

#include <string>
#include <codecvt>
#include <iostream>
#include <locale>
#include <fstream>

#include "../imageUtils/AsciiConverter.h"
#include "../inc/IConsole.hpp"

namespace ConsoleArt
{
class AsciiPrinter
{
private:
	ImageUtils::AsciiConverter& asciiCon;
	ConsoleUtils::IConsole& console;
	ConsoleUtils::Colors::Color color;
public:
	AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console);
	AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console, ConsoleUtils::Colors::Color color);
	~AsciiPrinter();
	void printClassic();
	void printPixelColored();
	void printCharColored();
	void printToFile();
};
} /* namespace Images */
#endif /* IMAGEUTILS_ASCIIPRINTER_H_ */
