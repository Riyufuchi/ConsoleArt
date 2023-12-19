//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : 18.12.2023
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>

#include "consoleArt/ConsoleArtTools.hpp"
#include "consoleArt/ControllerCLI.h"
#include "inc/ConsoleUtility.h"
#include "inc/UnixConsole.h"

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
	ConsoleUtils::UnixConsole unixConsole;
	ConsoleUtils::ConsoleUtility::header("\v    ConsoleArt V2.1\v   ");
	ConsoleArt::ControllerCLI consoleArt(unixConsole);
	switch(checkArgs(argc, argv, 2, consoleArt.getConslole()))
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
	if(argc == 1)
		return BootAction::CONTINUE;
	else if(!strcmp(argv[1], "--man") || !strcmp(argv[1], "--help")) //First argument is always app name if argc != 1, than check for manual
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
