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
		std::cout << "Manual\n";
		std::string args[7];
		args[0] = "Arguments| Actions";
		args[1] = "none| Workspace in same directory as executable";
		args[2] = "-p --path| Specify workspace folder";
		args[3] = "--colorTest| Print colored text for testing";
		args[4] = "--loadAll| Loads all images in workspace (must be after --path)";
		args[5] = "--image| Loads image in workspace (should be after --path)";
		args[6] = "--imagePath| Loads image with given path";
		ConsoleUtils::ConsoleUtility::createManual(args, sizeof(args)/sizeof(args[0]));
	}
	static void colorTest(ConsoleUtils::IConsole& console)
	{
		for (int i = 0; i < ConsoleUtils::ColorUtils::ColorPallete::COLOR_COUNT; ++i)
			console.out(ConsoleUtils::ColorUtils::getColor(static_cast<ConsoleUtils::ColorUtils::ColorPallete>(i)), std::string(ConsoleUtils::ColorUtils::colorPaletteNames[i]) + "\n");
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
