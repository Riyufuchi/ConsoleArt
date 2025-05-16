//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : Jul 13, 2020
// Last Edit   : May 16, 2025
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "consoleArt/controller/ControllerCLI.h"
#include "consoleArt/controller/ControllerZenity.h"
#include "consoleArt/controller/ControllerSDL.h"
#include "consoleArt/controller/ControllerTFD.h"
#include "consoleArt/tools/GeneralTools.hpp"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "IConsole.hpp"
#include "DefaultConsole.h"
#include "ArgumentParser.h"
#include "other/ScheduleTracker.h"
#include "sdl/assets/FontManagerSDL.h"
#ifdef _WIN32
	#include "WindowsConsole.h"
#endif // _WIN32

using ParsedArguments = ConsoleLib::argVector; // or ConsoleLib::argMap

enum BootAction
{
	ABORT,
	DISPLAY_MANUAL,
	CONFIGURE,
	CONTINUE,
	TEST,
	ABOUT,
	LIBRARY,
	SCHEDULE
};

BootAction checkArgs(ParsedArguments& argPairs, ConsoleLib::IConsole& console);

BootAction abort(ConsoleLib::IConsole& console)
{
	console.err("Unrecognized action. Aborting!");
	return BootAction::ABORT;
}

int main(int argc, char** argv)
{
	ConsoleLib::IConsole* systemConsole = ConsoleLib::ConsoleUtils::createPlatformConsole();

	if (systemConsole == nullptr)
	{
		std::cerr << "Failed to create platform console.\nExiting program!";
		return 1;
	}

	systemConsole->setDefaultTextColor(ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::APERTURE_ORANGE));

	ConsoleLib::ConsoleUtils::header("\n    " + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION) + "\n   ", *systemConsole);

	#ifdef _WIN32
		systemConsole->out(ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::UNIQUE),
			"Disclaimer: Windows in not a primarily targeted platform.\nThis build is experimental and some features might not be available or work correctly.\n");
	#endif

	bool success = true;
	std::string resultMsg = "";
	ParsedArguments argPairs = ConsoleLib::ArgumentParser::analyzeInOrder(argc, argv, success, resultMsg); // or just analyzeArguments(argc, argv, success, resultMsg);
	if (success)
		systemConsole->out(resultMsg + "\n");
	else
	{
		systemConsole->err(resultMsg + "\n");
		return 1;
	}

	#ifdef DEBUG
		systemConsole->out(153, 102, 51, "!!! This is a debug build !!!\n");
		ConsoleLib::ArgumentParser::printArgumentPairs(argPairs);
	#endif

	ConsoleArt::Controller* consoleArt;

	if (ConsoleLib::ArgumentParser::remove(argPairs, "--sdl"))
	{
		consoleArt = new ConsoleArt::ControllerSDL();
	}
	else if (ConsoleLib::ArgumentParser::remove(argPairs, "--zen"))
	{
		consoleArt = new ConsoleArt::ControllerZenity(systemConsole);
	}
	else if (ConsoleLib::ArgumentParser::remove(argPairs, "--tfd"))
	{
		consoleArt = new ConsoleArt::ControllerTFD(systemConsole);
	}
	else
	{
		consoleArt = new ConsoleArt::ControllerCLI(systemConsole);
	}

	if (consoleArt == nullptr)
		return 1;

	switch (checkArgs(argPairs, *systemConsole))
	{
		case ABORT: return 1;
		case CONTINUE: goto start;
		case CONFIGURE: goto conf;
		default: return 0; // For other cases that result in success
	}
	conf: consoleArt->configure(argPairs);
	start: consoleArt->run();
	delete consoleArt;
	delete systemConsole;
	return 0;
}

BootAction checkArgs(ParsedArguments& argPairs, ConsoleLib::IConsole& console)
{
	if (argPairs.empty())
		return BootAction::CONTINUE;

	const std::vector<std::pair<std::string, BootAction>> checkFor = {
		{"--man", BootAction::DISPLAY_MANUAL},
		{"--help", BootAction::DISPLAY_MANUAL},
		{"--colorTest", BootAction::TEST},
		{"--about", BootAction::ABOUT},
		{"--library", BootAction::LIBRARY},
		{"--schedule", BootAction::SCHEDULE}
	};

	for (std::pair<std::string, BootAction> arg : checkFor)
	{
		//if (argPairs.contains(arg.first))
		if (ConsoleLib::ArgumentParser::contains(argPairs, arg.first))
			switch (arg.second)
			{
				case DISPLAY_MANUAL: ConsoleArt::GeneralTools::createManual(); return arg.second;
				case TEST: ConsoleArt::GeneralTools::colorTest(console); return arg.second;
				case ABOUT: console.out(ConsoleArt::GeneralTools::aboutApplication()); return arg.second;
				case LIBRARY: console.out(ConsoleArt::GeneralTools::usedLibraries()); return arg.second;
				case SCHEDULE: Other::ScheduleTracker(console).run(); return arg.second;
				default: abort(console);
			}
	}

	return BootAction::CONFIGURE;
}
