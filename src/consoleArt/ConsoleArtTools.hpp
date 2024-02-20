//==============================================================================
// File       : ConsoleArtUtils.hpp
// Author     : riyufuchi
// Created on : Nov 23, 2023
// Last edit  : 18.12.2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONSOLEARTTOOLS_HPP_
#define CONSOLEART_CONSOLEARTTOOLS_HPP_

#include <iostream>
#include <string>

#include "../inc/ConsoleUtility.h"
#include "../inc/IConsole.hpp"
#include "../inc/UnixConsole.h"

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
		std::cout << "Riyufuchi (c) 2020 - 2024\n";
		std::string args[] = {
			"Arguments| Actions",
			"-p --path| Specify workspace folder",
			"--colorTest| Print colored text for testing",
			"--loadAll| Loads all images in workspace (must be after --path)",
			"--image| Loads image in workspace (should be after --path)",
			"--imagePath| Loads image with given path",
			"--no-color| Disable colored outputs, for when they are not supported"
		};
		ConsoleUtils::ConsoleUtility::createManual(args, sizeof(args)/sizeof(args[0]));
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
