//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : 16.03.2023
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

BootAction checkArgs(int argc, char** argv, int reqArgNum);

int main(int argc, char** argv)
{
	ConsoleUtility::header("\v    ConsoleArt V1.27\v   ");
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

BootAction createManual()
{
	std::cout << "Manual\n";
	std::string args[3];
	args[0] = "Arguments| Actions";
	args[1] = "none| in same directory as executable";
	args[2] = "-p --path| specify workspace";
	ConsoleUtility::createManual(args, sizeof(args)/sizeof(args[0]));
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
