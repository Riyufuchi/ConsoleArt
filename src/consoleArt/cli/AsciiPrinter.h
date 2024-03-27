//==============================================================================
// File       : AsciiPrinter.h
// Author     : Riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Mar 4, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _ASCII_PRINTER_H_
#define _ASCII_PRINTER_H_

#include <string>
#include <codecvt>
#include <iostream>
#include <locale>
#include <fstream>

#include "../../imageUtils/AsciiConverter.h"
#include "IConsole.hpp"
#include "ConsoleUtils.h"

namespace ConsoleArt
{
class AsciiPrinter
{
private:
	ImageUtils::AsciiConverter& asciiCon;
	ConsoleLib::IConsole& console;
	ConsoleLib::Color color;
public:
	AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleLib::IConsole& console);
	AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleLib::IConsole& console, ConsoleLib::Color color);
	~AsciiPrinter();
	void printClassic();
	void printPixelColored();
	void printCharColored();
	void printToFile();
};
} /* namespace Images */
#endif /* IMAGEUTILS_ASCIIPRINTER_H_ */
