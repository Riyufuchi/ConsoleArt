//==============================================================================
// File       : ConsoleArtUtils.hpp
// Author     : riyufuchi
// Created on : Nov 23, 2023
// Last edit  : Mar 8, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLE_ART_TOOLS_HPP_
#define _CONSOLE_ART_TOOLS_HPP_

#include <iostream>
#include <string>

#include "../inc/ConsoleUtils.h"
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
			"-p --path [path]| Specify workspace folder",
			"--colorTest| Print colored text for testing",
			"--loadAll| Loads all images in workspace (should be after --path)",
			"--image [path]| Loads given image (in workspace if defined)",
			"--no-color| Disable colored outputs, for when they are not supported",
			"--color [colorID]| Sets default text color",
			"--about| Shows details about this application"
		};
		ConsoleUtility::ConsoleUtils::createManual(args, sizeof(args)/sizeof(args[0]));
	}
	static void aboutApplication()
	{
		std::cout << _COPYRIGHT_HEADER;
		printf("This version was compiled on: %s %s\nC++ version: %ld\n\n", __DATE__, __TIME__, __cplusplus);
		std::cout << "This is an C++ application for converting images into ASCII/UNICODE.\n\n";

		std::cout << "How to use:\n";
		std::cout << "1. Select font where all characters have same width\n";
		std::cout << "2. Load and select image\n";
		std::cout << "3. Convert image\n";
		std::cout << "4. In order to view the image, make font smaller. Size 2 is recommended for bigger images, however this depends on size of given image\n\n";

		std::cout << "Supported image formats\n";
		const char* format =
					"%s\n"
					"  bits:\n"
					"    %s\n"
					"  Note:\n"
					"    %s\n\n";
		printf(format, "PCX", "24, 32", "Only compressed");
		printf(format, "BMP", "24, 32", "Bottom left corner start oriented\n    Uncompressed sRGB");

	}
	static void colorTest(ConsoleUtility::IConsole& console)
	{
		for (int i = 0; i < ConsoleUtility::ColorPallete::COLOR_COUNT; ++i)
		{
			std::cout << i + 1 << ". ";
			console.out(ConsoleUtility::ColorUtils::getColor(static_cast<ConsoleUtility::ColorPallete>(i)), ConsoleUtility::ColorUtils::colorPaletteNames[i]);
			std::cout << "\n";
		}
	}
	static void printArgError(const char* arg, ConsoleUtility::IConsole& console)
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
} // Namespace
#endif /* CONSOLEART_CONSOLEARTTOOLS_HPP_ */
