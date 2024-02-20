//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : 20.02.2024
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
	#if defined(__linux__) || defined(__APPLE__)
		ConsoleUtils::UnixConsole sysConsole;
	#else
		ConsoleUtils::DefaultConsole sysConsole;
	#endif
	ConsoleUtils::IConsole& con = sysConsole;
	con.setDefaultTextColor(color);
	ConsoleUtils::ConsoleUtility::header("\v    ConsoleArt V2.0\v   ", con, color);
	ConsoleArt::ControllerCLI consoleArt(&con);
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
