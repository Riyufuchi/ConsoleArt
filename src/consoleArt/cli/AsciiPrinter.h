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
#include "../../inc/IConsole.hpp"
#include "../../inc/ConsoleUtility.h"

namespace ConsoleArt
{
class AsciiPrinter
{
private:
	ImageUtils::AsciiConverter& asciiCon;
	ConsoleUtils::IConsole& console;
	ConsoleUtils::Color color;
public:
	AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console);
	AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console, ConsoleUtils::Color color);
	~AsciiPrinter();
	void printClassic();
	void printPixelColored();
	void printCharColored();
	void printToFile();
};
} /* namespace Images */
#endif /* IMAGEUTILS_ASCIIPRINTER_H_ */
