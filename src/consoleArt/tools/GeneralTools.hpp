//==============================================================================
// File       : GeneralTools.hpp
// Author     : riyufuchi
// Created on : Nov 23, 2023
// Last edit  : Feb 17, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLE_ART_GENERAL_TOOLS_HPP_
#define _CONSOLE_ART_GENERAL_TOOLS_HPP_

#include <iostream>
#include <string>
#include <array>

#include "ConsoleUtils.h"
#include "IConsole.hpp"
#include "Library.h"

#define _COPYRIGHT_HEADER "Riyufuchi (c) 2020 - 2025\n"

namespace ConsoleArt
{
enum Argumemts
{
	LOAD_ALL,
	IMAGE,
	PATH,
	COLOR,
	NO_COLOR,
	CLIENT,
	BENCHMARK,
	BINOM,
	COMPARE
};
class GeneralTools
{
public:
	static constexpr const char* CONSOLE_ART_VERSION = "2.8 - beta 9";
	GeneralTools();
	~GeneralTools();
	static constexpr  std::array<std::pair<const char*, Argumemts>, (Argumemts::COMPARE + 2)> arguments()
	{
		return {{
			{"-p", Argumemts::PATH},
			{"--path", Argumemts::PATH},
			{"--loadAll", Argumemts::LOAD_ALL},
			{"--image", Argumemts::IMAGE},
			{"--color", Argumemts::COLOR},
			{"--no-color", Argumemts::NO_COLOR},
			{"--client", Argumemts::CLIENT},
			{"--benchmark", Argumemts::BENCHMARK},
			{"--BI", Argumemts::BINOM},
			{"--compare", Argumemts::COMPARE}
		}};
	}
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
			"--about| Shows details about this application",
			"--client [IP address (optional)]| Starts ConsoleArt as simple client, that connects to server",
			"--server| Starts ConsoleArt as simple server (port 6969)",
			"--benchmark [path (optional)]| Starts simple benchmark that loads and convert image (default file: bench.pcx)",
			"--BI [N, P, K...]| Binomial distribution",
			"--library| Shows info about ConsoleLib and other used libraries besides standard and platform depended",
			"--compare [image1] [image2]| Compares two images",
			"--cli| Starts application in CLI mode (default)",
			"--zen| Starts application in CLI mode using Zenity"
		};
		ConsoleLib::ConsoleUtils::createManual(args, sizeof(args)/sizeof(args[0]));
	}
	static std::string aboutApplication()
	{
		std::stringstream aboutStringStream;
		aboutStringStream << _COPYRIGHT_HEADER;
		aboutStringStream << "This version was compiled on: " << __DATE__ << " " << __TIME__ << "\n";
		aboutStringStream << "C++ version: " << __cplusplus << "\n";

		aboutStringStream << "This is an C++ application for converting images into ASCII/UNICODE.\n\n";

		aboutStringStream << "How to use:\n";
		aboutStringStream << "1. Select font (in your console/terminal) where all characters have same width\n";
		aboutStringStream << "2. Load and select image\n";
		aboutStringStream << "3. Convert image\n";
		aboutStringStream << "4. In order to view the image, make font smaller. Size 2 is recommended for bigger images, however this depends on size of given image\n\n";

		aboutStringStream << "Supported image formats\n";
		std::string args[] = {
					"Format| Bits; Notes",
					"PCX| 24, 32; VGA palette",
					"BMP| 24, 32; Bottom left corner start oriented, Uncompressed BGRA",
					"PPM| 24;",
					"PNG| 24, 32;"
				};
		aboutStringStream << ConsoleLib::ConsoleUtils::createTable(args, sizeof(args)/sizeof(args[0]));

		aboutStringStream << "\n" << "Used libraries:\n" << ConsoleLib::Library::aboutLibrary();

		std::string libs[] = {
					"Name| Used for",
					"stb | complex images",
					"SDL2| GUI",
				};
		aboutStringStream << "\n" << ConsoleLib::ConsoleUtils::createTable(libs, sizeof(libs)/sizeof(libs[0]));
		return aboutStringStream.str();
	}
	static void colorTest(ConsoleLib::IConsole& console)
	{
		for (int i = 0; i < ConsoleLib::ColorPallete::COLOR_COUNT; ++i)
		{
			std::cout << i + 1 << ". ";
			console.out(ConsoleLib::ColorUtils::getColor(static_cast<ConsoleLib::ColorPallete>(i)), ConsoleLib::ColorUtils::colorPaletteNames[i]);
			std::cout << "\n";
		}
	}
	static std::string createArgErrorMessage(std::string arg)
	{
		return std::string("Invalid or unknown ").append(arg).append(" inputed.\nUse --man or --help for help.\n");
	}
};
} // Namespace
#endif /* _CONSOLE_ART_GENERAL_TOOLS_HPP_ */
