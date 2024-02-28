//==============================================================================
// File       : ConsoleArtUtils.hpp
// Author     : riyufuchi
// Created on : Nov 23, 2023
// Last edit  : Feb 28, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLE_ART_TOOLS_HPP_
#define _CONSOLE_ART_TOOLS_HPP_

#include <iostream>
#include <string>

#include "../inc/ConsoleUtility.h"
#include "../inc/IConsole.hpp"

#define _COPYRIGHT_HEADER "Riyufuchi (c) 2020 - 2024\n"

namespace ConsoleArt
{
class ConsoleArtTools
{
private:
public:
	ConsoleArtTools();
	~ConsoleArtTools();
	static void createManual()
	{
		std::cout << _COPYRIGHT_HEADER;
		std::string args[] = {
			"Arguments| Actions",
			"-p --path| Specify workspace folder",
			"--colorTest| Print colored text for testing",
			"--loadAll| Loads all images in workspace (should be after --path)",
			"--image| Loads given image (in workspace if defined)",
			"--no-color| Disable colored outputs, for when they are not supported",
			"--about| Shows details about this application"
		};
		ConsoleUtils::ConsoleUtility::createManual(args, sizeof(args)/sizeof(args[0]));
	}
	static void aboutApplication()
	{
		std::cout << _COPYRIGHT_HEADER;
		printf("This version was compiled on: %s %s\n", __DATE__, __TIME__);
		std::cout << "This is an C++ application for converting images into ASCII/UNICODE.\n";
	}
	static void colorTest(ConsoleUtils::IConsole& console)
	{
		for (int i = 0; i < ConsoleUtils::ColorPallete::COLOR_COUNT; ++i)
			console.out(ConsoleUtils::ColorUtils::getColor(static_cast<ConsoleUtils::ColorPallete>(i)), std::string(ConsoleUtils::ColorUtils::colorPaletteNames[i]) + "\n");
	}
	static void printArgError(const char* arg, ConsoleUtils::IConsole& console)
	{
		std::string errMsg = "Invalid or unknown ";
		errMsg += arg;
		console.out(255, 0, 0, errMsg.append(" inputed.\n"));
		std::cout << "Use --man or --help for help.\n";
	}
	static std::string createArgErrorMessage(const char* arg)
	{
		std::string errMsg = "Invalid or unknown ";
		errMsg += arg;
		return errMsg.append(" inputed.\nUse --man or --help for help.\n");
	}
};
}
#endif /* CONSOLEART_CONSOLEARTTOOLS_HPP_ */
