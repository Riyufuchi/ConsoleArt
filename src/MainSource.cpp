//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : 12.03.2023
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "consoleUtils/ConsoleUtility.h"
#include "controller/Controller.h"

enum BootAction
{
	ABORT,
	DISPLAY_MANUAL,
	CONFIGURE,
	CONTINUE
};

BootAction createManual()
{
	std::cout << "Argument" << "Action\n";
	std::cout << "empty arguments" << " path same as for executable";
	std::cout << "-p --path" << " path to img folder";
	return BootAction::DISPLAY_MANUAL;
}

BootAction printError()
{
	std::cerr << "Invalid or unknown arguments inputed.\nUse -man for help.\n";
	return BootAction::ABORT;
}

BootAction checkArgs(int argc, char** argv, int reqArgNum)
{
	if(argc == 1)
		return BootAction::CONTINUE;
	else if(!strcmp(argv[1], "-man")) //First argument is always app name if argc != 1, than check for manual
		return createManual();
	else if(argc < reqArgNum) //If argc is less than minimum then arguments are invalid
		return printError();
	else
		return BootAction::CONFIGURE;
}

int main(int argc, char** argv)
{
	ConsoleUtility::header("\v    ConsoleArt V1.22\v   ");
	Controller con;
	switch(checkArgs(argc, argv, 3))
	{
		case ABORT: return 1;
		case CONTINUE: goto start;
		case CONFIGURE: goto conf;
		case DISPLAY_MANUAL: return 0;
	}
	conf: con.configure(argc, argv);
	start: con.run();
	return 0;
}
