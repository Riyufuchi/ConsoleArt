//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : 15.11.2022
// Description : This program main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "consoleUtils/ConsoleUtility.h"
#include "controller/Controller.h"

int createManual()
{
	std::cout << "Argument" << "Action\n";
	std::cout << "empty arguments" << " path same as for executable";
	std::cout << "-p --path" << " path to img folder";
	return 0; //manual was displayed and app is closed
}

int printError()
{
	std::cerr << "Invalid or unknown arguments inputed.\nUse -man for help.\n";
	return 1;
}

int main(int argc, char** argv)
{
	ConsoleUtility::header("\v    Image to ASCII converter V1.0\v   ");
	std::string path = "";
	if(argc == 1) //First argument is always app name
	{
		std::cout << "Loading files in app folder selected.\n";
	}
	else if(!strcmp(argv[1], "-man")) //if argc isn't 1, than check for manual
	{
		return createManual();
	}
	else if (argc < 3) //3 is number of required arguments, if it less and not manual argument, input is invalid
	{
		return printError();
	}
	else if(!strcmp(argv[1], "-p") || !strcmp(argv[1], "-path"))
	{
		//std::string path2{argv[2]};
		path = reinterpret_cast<const char*>((argv[2]));
		std::cout << "Selected path: " << path << "\n";
	}
	else
	{
		return printError();
	}
	Controller con(path);
	con.run();
	return 0;
}
