//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : Jul 13, 2020
// Last Edit   : Jan 14, 2025
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "consoleArt/controller/ControllerCLI.h"
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

BootAction checkArgs(int argc, char** argv, int reqArgNum, ConsoleLib::IConsole& console);

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

	ConsoleLib::ConsoleUtils::header("\n    ConsoleArt v" + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION) +"\n   ", systemConsole, color);

	ConsoleArt::Controller* consoleArt;
	if (argPairs.contains("--zen"))
		consoleArt = new ConsoleArt::ControllerGuiZen(&systemConsole);
	else
		consoleArt = new ConsoleArt::ControllerCLI(&systemConsole);

	switch(checkArgs(argc, argv, 2, systemConsole))
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

BootAction checkArgs(int argc, char** argv, int reqArgNum, ConsoleLib::IConsole& console)
{
	if(argc == 1) // First argument is always app name
		return BootAction::CONTINUE;
	else if(!strcmp(argv[1], "--man") || !strcmp(argv[1], "--help"))
	{
		ConsoleArt::GeneralTools::createManual();
		return BootAction::DISPLAY_MANUAL;
	}
	else if(!strcmp(argv[1], "--colorTest"))
	{
		ConsoleArt::GeneralTools::colorTest(console);
		return BootAction::TEST;
	}
	else if(!strcmp(argv[1], "--runServer"))
	{
		#if defined(_WIN32)
			console.out("Server is available only in Linux/Unix version.");
		#else
			ConsoleArt::ServerTools server;
			server.startServerThread();
		#endif
		return BootAction::SERVER;
	}
	else if(argc < reqArgNum) //If argc is less than minimum then arguments are invalid
	{
		ConsoleArt::GeneralTools::printArgError(argv[1], console);
		return BootAction::ABORT;
	}
	else
		return BootAction::CONFIGURE;
}
