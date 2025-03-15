//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : Jul 13, 2020
// Last Edit   : Feb 27, 2025
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "consoleArt/controller/ControllerCLI.h"
#include "consoleArt/controller/ControllerZenity.h"
#include "consoleArt/controller/ControllerSDL.h"
#include "consoleArt/network/server/ServerTools.h"
#include "consoleArt/tools/GeneralTools.hpp"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "IConsole.hpp"
#include "DefaultConsole.h"
#include "consoleArt/network/server/Server.h"
#include "other/ScheduleTracker.h"
#include "sdl/assets/FontManagerSDL.h"
#ifdef _WIN32
	#include "WindowsConsole.h"
#endif // _WIN32

enum BootAction
{
	ABORT,
	DISPLAY_MANUAL,
	CONFIGURE,
	CONTINUE,
	TEST,
	SERVER,
	ABOUT,
	LIBRARY,
	SCHEDULE
};

BootAction checkArgs(std::map<std::string, std::vector<std::string>>& argPairs, ConsoleLib::IConsole& console);

BootAction abort(ConsoleLib::IConsole& console)
{
	console.err("Unrecognized action. Aborting!");
	return BootAction::ABORT;
}

int main(int argc, char** argv)
{
	ConsoleLib::Color color = ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::APERTURE_ORANGE);
	#if defined(__linux__) || defined(__APPLE__)
		ConsoleLib::UnixConsole systemConsole;
	#elif defined(_WIN32)
		ConsoleLib::WindowsConsole systemConsole;
		systemConsole.out(ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::UNIQUE),
			"Disclaimer: Windows in not a primarily targeted platform.\nThis build is experimental and some features might not be available or work correctly.\n");
	#else
		ConsoleLib::DefaultConsole systemConsole;
	#endif
	systemConsole.setDefaultTextColor(color);

	ConsoleLib::ConsoleUtils::header("\n    " + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION) + "\n   ", systemConsole, color);

	bool success = true;
	std::string resultMsg = "";
	std::map<std::string, std::vector<std::string>> argPairs = ConsoleLib::ConsoleUtils::analyzeArguments(argc, argv, success, resultMsg);
	if (success)
		systemConsole.out(resultMsg + "\n");
	else
	{
		systemConsole.err(resultMsg + "\n");
		return 1;
	}

	#ifdef DEBUG
		systemConsole.out(153, 102, 51, "!!! This is a debug build !!!\n");
		ConsoleLib::ConsoleUtils::printArgumentPairs(argPairs);
	#endif

	ConsoleArt::Controller* consoleArt;

	if (argPairs.contains("--sdl"))
	{
		argPairs.erase("--sdl");
		consoleArt = new ConsoleArt::ControllerSDL();
	}
	else if (argPairs.contains("--zen"))
	{
		argPairs.erase("--zen");
		consoleArt = new ConsoleArt::ControllerZenity(&systemConsole);
	}
	else
	{
		consoleArt = new ConsoleArt::ControllerCLI(&systemConsole);
	}

	switch (checkArgs(argPairs, systemConsole))
	{
		case ABORT: return 1;
		case CONTINUE: goto start;
		case CONFIGURE: goto conf;
		default: return 0; // For other cases that result in success
	}
	conf: consoleArt->configure(argPairs);
	start: consoleArt->run();
	sdl::FontManagerSDL::getInstance().clear();
	delete consoleArt;
	return 0;
}

BootAction checkArgs(std::map<std::string, std::vector<std::string>>& argPairs, ConsoleLib::IConsole& console)
{
	if (argPairs.empty()) // First argument is always app name
		return BootAction::CONTINUE;

	const std::vector<std::pair<std::string, BootAction>> checkFor = {
		{"--man", BootAction::DISPLAY_MANUAL},
		{"--help", BootAction::DISPLAY_MANUAL},
		{"--colorTest", BootAction::TEST},
		{"--server", BootAction::SERVER},
		{"--about", BootAction::ABOUT},
		{"--library", BootAction::LIBRARY},
		{"--schedule", BootAction::SCHEDULE}
	};

	for (std::pair<std::string, BootAction> arg : checkFor)
	{
		if (argPairs.contains(arg.first))
			switch (arg.second)
			{
				case DISPLAY_MANUAL: ConsoleArt::GeneralTools::createManual(); return arg.second;
				case TEST: ConsoleArt::GeneralTools::colorTest(console); return arg.second;
				case SERVER: {
					#if defined(_WIN32)
						console.out("Server is available only in Linux/Unix version.");
					#else
						ConsoleArt::ServerTools server;
						server.startServerThread();
					#endif
					return arg.second;
				}
				case ABOUT: console.out(ConsoleArt::GeneralTools::aboutApplication()); return arg.second;
				case LIBRARY:
					console.out(ConsoleLib::Library::aboutLibrary());
					console.out("\nstb\n");
				return arg.second;
				case SCHEDULE: {
					Other::ScheduleTracker schedule(console);
					schedule.run();
				}return arg.second;
				default: abort(console);
			}
	}

	return BootAction::CONFIGURE;
}
