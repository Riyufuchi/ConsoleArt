//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : Jul 13, 2020
// Last Edit   : Dec 23, 2025
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "console_art/controller/ControllerCLI.h"
#include "console_art/controller/ControllerSDL.h"
#include "console_art/controller/ControllerTFD.h"
#include "console_art/tools/general_tools.hpp"
#include "other/ScheduleTracker.h"
//
#include "consolelib/consoles.hpp"
#include "consolelib/tools/argument_parser.h"
#include "consolelib/tools/console_tools.h"


using ParsedArguments = consolelib::argVector; // or consolelib::argMap

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

BootAction checkArgs(ParsedArguments& argPairs, consolelib::IConsole& console);

BootAction abort(consolelib::IConsole& console)
{
	console.err("Unrecognized action. Aborting!");
	return BootAction::ABORT;
}

int main(int argc, char** argv)
{
	consolelib::IConsole* systemConsole = consolelib::console_tools::createPlatformConsole();

	if (systemConsole == nullptr)
	{
		std::cerr << "Failed to create platform console.\nExiting program!";
		return 1;
	}

	systemConsole->setDefaultTextColor(consolelib::color_tools::getColor(consolelib::ColorPallete::APERTURE_ORANGE));

	consolelib::console_tools::header("\n    " + std::string(consoleart::general_tools::CONSOLE_ART_VERSION) + "\n   ", *systemConsole);

	bool success = true;
	std::string resultMsg = "";
	ParsedArguments argPairs = consolelib::ArgumentParser::analyzeInOrder(argc, argv, success, resultMsg); // or just analyzeArguments(argc, argv, success, resultMsg);
	if (success)
		systemConsole->out(resultMsg + "\n");
	else
	{
		systemConsole->err(resultMsg + "\n");
		return 1;
	}

	#ifdef DEBUG
		systemConsole->out(153, 102, 51, "!!! This is a debug build !!!\n");
		consolelib::ArgumentParser::printArgumentPairs(argPairs);
	#endif

	consoleart::Controller* consoleArt;

	if (consolelib::ArgumentParser::remove(argPairs, "--noGUI"))
	{
		consoleArt = new consoleart::ControllerCLI(systemConsole);
	}
	else if (consolelib::ArgumentParser::remove(argPairs, "--tfd"))
	{
		consoleArt = new consoleart::ControllerTFD(systemConsole);
	}
	else
	{
		consoleArt = new consoleart::ControllerSDL();
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

BootAction checkArgs(ParsedArguments& argPairs, consolelib::IConsole& console)
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
		if (consolelib::ArgumentParser::contains(argPairs, arg.first))
			switch (arg.second)
			{
				case DISPLAY_MANUAL: consoleart::general_tools::createManual(); return arg.second;
				case TEST: consoleart::general_tools::colorTest(console); return arg.second;
				case ABOUT: console.out(consoleart::general_tools::aboutApplication()); return arg.second;
				case LIBRARY: console.out(consoleart::general_tools::usedLibraries()); return arg.second;
				case SCHEDULE: Other::ScheduleTracker(console).run(); return arg.second;
				default: abort(console);
			}
	}

	return BootAction::CONFIGURE;
}
