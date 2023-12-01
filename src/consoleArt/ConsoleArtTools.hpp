//==============================================================================
// File       : ConsoleArtUtils.hpp
// Author     : riyufuchi
// Created on : Nov 23, 2023
// Last edit  : Nov 23, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONSOLEARTTOOLS_HPP_
#define CONSOLEART_CONSOLEARTTOOLS_HPP_

#include <iostream>
#include <string>

#include "../inc/ConsoleUtility.h"
#include "../inc/IConsole.hpp"

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
	static void colorTest()
	{
		ConsoleUtils::UnixConsole uc;
		for (int i = 0; i < ConsoleUtils::Colors::ColorPallete::COLOR_COUNT; ++i)
			uc.out(ConsoleUtils::Colors::getColor(static_cast<ConsoleUtils::Colors::ColorPallete>(i)), std::string(ConsoleUtils::Colors::colorPaletteNames[i]) + "\n");
	}
	static void printArgError(const char* arg, ConsoleUtils::IConsole& console)
	{
		std::string errMsg = "Invalid or unknown ";
		errMsg += arg;
		console.out(255, 0, 0, errMsg.append(" inputed.\n"));
		std::cout << "Use --man or --help for help.\n";
	}
};
}
#endif /* CONSOLEART_CONSOLEARTTOOLS_HPP_ */
