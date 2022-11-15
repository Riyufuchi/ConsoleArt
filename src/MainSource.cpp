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
#include "ConsoleUtility.h"
#include "ImageBMP.h"
#include "UnixConsole.h"
#include "imgUtils/AsciiConverter.h"

ImageBMP loadImage(std::string defaultPath)
{
	std::cout << "Image name without file extension (only .bmp images):" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	imgName.append(".bmp");
	ImageBMP img((defaultPath.append(imgName)).c_str());
	return img;
}

int menuDelegation()
{
	const char* menuItems[] = { "BASIC - █#@%=+:-. ", "PRECISE", "DEATAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█" };
	return ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
}

void linuxVersion(ImageBMP img)
{
	if(img.getFilename() != std::string("NULL"))
	{
		UnixConsole uc;
		AsciiConverter ac(img);
		ac.setCharSet(menuDelegation());
		//img.setCharSet(menuDelegation());
		std::cout << "Press Enter to continue..." << std::endl;
		std::cin.get();
		std::cin.get();
		std::cout << "Processing image..." << std::endl;
		ac.convertToASCII();
		//img.convertToASCII(); //Converts image to chars and save it in array
		if (ConsoleUtility::yesNo("Custom color [Y/n]: "))
		{
			std::cout << "Red: ";
			int red = ConsoleUtility::getIntSafe(0, 255);
			std::cout << "Green: ";
			int green = ConsoleUtility::getIntSafe(0, 255);
			std::cout << "Blue: ";
			int blue = ConsoleUtility::getIntSafe(0, 255);
			uc.setMainTextColor(uc.setColor(red, green, blue));
		}
		//Explicit outputting of converted image
		const int height = img.getBmpInfo().height;
		for(int i = 0; i < height; i++)
		{
			uc.writeText(ac.getLine(i));
		}
		//Implicit:
		//img.outputAsciiImage();
	}
	std::cin.get(); //Catch enter character - if not, user will press enter anyway
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
		std::cout << "Argument" << "Action\n";
		std::cout << "empty arguments" << "path same as for executable";
		std::cout << "-p --path" << "path to img folder";
		return 0; //manual was displayed and app is closed
	}
	else if (argc < 3) //3 is number of required arguments, if it less and not manual argument, input is invalid
	{
		std::cerr << "Invalid or unknown arguments inputed.\nUse -man for help.\n";
		return 1;
	}
	else if(!strcmp(argv[1], "-p") || !strcmp(argv[1], "-path"))
	{
		//std::string path2{argv[2]};
		path = reinterpret_cast<const char*>((argv[2]));
		std::cout << "Path " << path << " selected.\n";
	}
	else
	{
		std::cerr << "Invalid or unknown arguments inputed.\nUse -man for help.\n";
		return 1;
	}

	do
	{
		linuxVersion(loadImage(path));
	}while(ConsoleUtility::repeat());
	return 0;
}
