//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : 23.11.2023
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>

#include "consoleArt/UnixControllerCLI.h"
#include "consoleArt/ConsoleArt.hpp"
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
	ConsoleUtils::ConsoleUtility::header("\v    ConsoleArt V1.97\v   ");
	ConsoleArt::UnixControllerCLI unixController;
	switch(checkArgs(argc, argv, 2, unixController.getUnixConslole()))
	{
		case ABORT: return 1;
		case CONTINUE: goto start;
		case CONFIGURE: goto conf;
		case TEST: return 0;
		case DISPLAY_MANUAL: return 0;
	}
	conf: unixController.configure(argc, argv);
	start: unixController.run();
	return 0;
}

BootAction checkArgs(int argc, char** argv, int reqArgNum, ConsoleUtils::IConsole& console)
{
	if(argc == 1)
		return BootAction::CONTINUE;
	else if(!strcmp(argv[1], "--man") || !strcmp(argv[1], "--help")) //First argument is always app name if argc != 1, than check for manual
	{
		ConsoleArt::ConsoleArt::createManual();
		return BootAction::DISPLAY_MANUAL;
	}
	else if(!strcmp(argv[1], "--colorTest"))
	{
		ConsoleArt::ConsoleArt::colorTest();
		return BootAction::TEST;
	}
	else if(argc < reqArgNum) //If argc is less than minimum then arguments are invalid
	{
		ConsoleArt::ConsoleArt::printArgError(argv[1], console);
		return BootAction::ABORT;
	}
	else
		return BootAction::CONFIGURE;
}
