//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : 22.11.2023
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>

#include "consoleArt/UnixControllerCLI.h"
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

BootAction checkArgs(int argc, char** argv, int reqArgNum);

int main(int argc, char** argv)
{
	ConsoleUtils::ConsoleUtility::header("\v    ConsoleArt V1.95\v   ");
	ConsoleArt::UnixControllerCLI unixController;
	switch(checkArgs(argc, argv, 3))
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

BootAction createManual()
{
	std::cout << "Manual\n";
	std::string args[5];
	args[0] = "Arguments| Actions";
	args[1] = "none| Workspace in same directory as executable";
	args[2] = "-p --path| Specify workspace folder";
	args[3] = "--colorTest| Print colored text for testing";
	args[4] = "--loadAll| Loads all images in workspace (must be after --path)";
	ConsoleUtils::ConsoleUtility::createManual(args, sizeof(args)/sizeof(args[0]));
	return BootAction::DISPLAY_MANUAL;
}

BootAction printError()
{
	std::cerr << "Invalid or unknown arguments inputed.\nUse -man for help.\n";
	return BootAction::ABORT;
}

BootAction colorTest()
{
	ConsoleUtils::UnixConsole uc;
	for (int i = 0; i < ConsoleUtils::Colors::ColorPallete::COLOR_COUNT; ++i)
	uc.writeText(ConsoleUtils::Colors::getColor(static_cast<ConsoleUtils::Colors::ColorPallete>(i)), ConsoleUtils::Colors::colorPaletteNames[i]);
	return BootAction::TEST;
}

BootAction checkArgs(int argc, char** argv, int reqArgNum)
{
	if(argc == 1)
		return BootAction::CONTINUE;
	else if(!strcmp(argv[1], "-man")) //First argument is always app name if argc != 1, than check for manual
		return createManual();
	else if(!strcmp(argv[1], "--colorTest")) //First argument is always app name if argc != 1, than check for manual
			return colorTest();
	else if(argc < reqArgNum) //If argc is less than minimum then arguments are invalid
		return printError();
	else
		return BootAction::CONFIGURE;
}
