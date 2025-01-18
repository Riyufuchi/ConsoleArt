//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : Jul 13, 2020
// Last Edit   : Jan 18, 2025
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "consoleArt/cli/ControllerCLI.h"
#include "consoleArt/gui/zenity/ControllerGuiZen.h"
#include "consoleArt/tools/ServerTools.h"
#include "consoleArt/tools/GeneralTools.hpp"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "IConsole.hpp"
#include "DefaultConsole.h"
#include "Server.h"
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
	SERVER
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

	ConsoleLib::ConsoleUtils::header("\n    ConsoleArt v" + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION) + "\n   ", systemConsole, color);

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

	ConsoleArt::Controller* consoleArt;
	if (argPairs.contains("--zen"))
		consoleArt = new ConsoleArt::ControllerGuiZen(&systemConsole);
	else
		consoleArt = new ConsoleArt::ControllerCLI(&systemConsole);

	switch(checkArgs(argPairs, systemConsole))
	{
		case ABORT: return 1;
		case CONTINUE: goto start;
		case CONFIGURE: goto conf;
		case TEST: return 0;
		case DISPLAY_MANUAL: return 0;
		case SERVER: return 0;
	}
	conf: consoleArt->configure(argc, argv);
	start: consoleArt->run();
	delete consoleArt;
	return 0;
}

BootAction checkArgs(std::map<std::string, std::vector<std::string>>& argPairs, ConsoleLib::IConsole& console)
{
	if (argPairs.size() <= 1) // First argument is always app name
			return BootAction::CONTINUE;

	const std::vector<std::pair<std::string, BootAction>> checkFor = {
		{"--man", BootAction::DISPLAY_MANUAL},
		{"--help", BootAction::DISPLAY_MANUAL},
		{"--colorTest", BootAction::TEST},
		{"--runServer", BootAction::SERVER}
	};

	for (std::pair<std::string, BootAction> arg : checkFor)
	{
		if (argPairs.contains(arg.first))
			switch (arg.second)
			{
				case DISPLAY_MANUAL: ConsoleArt::GeneralTools::createManual(); return BootAction::DISPLAY_MANUAL;
				case TEST: ConsoleArt::GeneralTools::colorTest(console); return BootAction::TEST;
				case SERVER: {
					#if defined(_WIN32)
						console.out("Server is available only in Linux/Unix version.");
					#else
						ConsoleArt::ServerTools server;
						server.startServerThread();
					#endif
					return BootAction::SERVER;
				}
				default: abort(console);
			}
	}

	return BootAction::CONFIGURE;
}
