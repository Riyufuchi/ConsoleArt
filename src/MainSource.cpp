//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : Mar 04, 2024
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>

#include "consoleArt/ConsoleArtTools.hpp"
#include "consoleArt/controller/ControllerCLI.h"
#include "inc/ConsoleUtility.h"
#include "inc/UnixConsole.h"
#include "inc/IConsole.hpp"
#include "inc/DefaultConsole.h"
#ifdef _WIN32
	#include "inc/WindowsConsole.h"
#endif // _WIN32


enum BootAction
{
	ABORT,
	DISPLAY_MANUAL,
	CONFIGURE,
	CONTINUE,
	TEST
};

BootAction checkArgs(int argc, char** argv, int reqArgNum, ConsoleUtils::IConsole& console);

int main(int argc, char** argv)
{
	ConsoleUtils::Color color = ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::APERTURE_ORANGE);
	//ConsoleUtils::IConsole& systemConsole2 = ConsoleUtils::DefaultConsole();
	#if defined(__linux__) || defined(__APPLE__)
		ConsoleUtils::UnixConsole systemConsole;
	#elif defined(_WIN32)
		ConsoleUtils::WindowsConsole systemConsole;
		systemConsole.out("Disclaimer: This is experimental Windows build, not all functionality may work correctly\n");
	#else
		ConsoleUtils::DefaultConsole systemConsole;
	#endif
	systemConsole.setDefaultTextColor(color);
	ConsoleUtils::ConsoleUtility::header("\n    ConsoleArt V2.1\n   ", systemConsole, color);
	ConsoleArt::ControllerCLI consoleArt(&systemConsole);
	switch(checkArgs(argc, argv, 2, *consoleArt.getConsole()))
	{
		case ABORT: return 1;
		case CONTINUE: goto start;
		case CONFIGURE: goto conf;
		case TEST: return 0;
		case DISPLAY_MANUAL: return 0;
	}
	conf: consoleArt.configure(argc, argv);
	start: consoleArt.run();
	return 0;
}

BootAction checkArgs(int argc, char** argv, int reqArgNum, ConsoleUtils::IConsole& console)
{
	if(argc == 1) // First argument is always app name
		return BootAction::CONTINUE;
	else if(!strcmp(argv[1], "--man") || !strcmp(argv[1], "--help"))
	{
		ConsoleArt::ConsoleArtTools::createManual();
		return BootAction::DISPLAY_MANUAL;
	}
	else if(!strcmp(argv[1], "--colorTest"))
	{
		ConsoleArt::ConsoleArtTools::colorTest(console);
		return BootAction::TEST;
	}
	else if(argc < reqArgNum) //If argc is less than minimum then arguments are invalid
	{
		ConsoleArt::ConsoleArtTools::printArgError(argv[1], console);
		return BootAction::ABORT;
	}
	else
		return BootAction::CONFIGURE;
}
