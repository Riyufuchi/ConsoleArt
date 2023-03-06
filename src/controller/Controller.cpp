//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 06.03.2023
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

Controller::Controller() : Controller("") //Calls constructor with parameter to construct class
{
}

Controller::Controller(std::string path)
{
	this->workspacePath = path;
}

//NOTE: This will need a little rework, if more application arguments would be expected
void Controller::configure(int argc, char** argv)
{
	if(!strcmp(argv[1], "-p") || !strcmp(argv[1], "--path"))
	{
		std::string path = reinterpret_cast<const char*>((argv[2])); //or std::string path{argv[2]};
		if((path.substr(path.length() - 1) != "/") && (path.length() > 0)) //if(argv[2][path.length() - 1] == '/')
			path.append("/");
		workspacePath = path;
	}
}

//TODO: Add option to reuse previous image
void Controller::run()
{
	//int imageID = bmpImages.size() - 1;
	do
	{
		linuxVersion(loadImage(workspacePath));
	}while(ConsoleUtility::repeat());
}

int Controller::createMenu()
{
	const char* menuItems[] = { "BASIC - █#@%=+:-. ", "PRECISE", "DEATAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█" };
	return ConsoleUtility::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems);
}

ImageBMP Controller::loadImage(std::string path)
{
	std::cout << "Image name without file extension - only bitmap (.bmp) images:" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); //Clears enter from console
	return ImageBMP (path + imgName.append(".bmp"));
}

void Controller::confConsoleColor(UnixConsole& unxConsole)
{
	if(ConsoleUtility::yesNo("Custom color [Y/n]: "))
	{
		std::cout << "Red: ";
		int red = ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Green: ";
		int green = ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Blue: ";
		int blue = ConsoleUtility::getIntSafe(0, 255);
		unxConsole.setTextColor(unxConsole.newColor(red, green, blue));
		std::cin.get(); //Catch enter character
	}
}

void Controller::linuxVersion(ImageBMP image)
{
	if(!image.isLoaded())
		return;
	UnixConsole uc;
	AsciiConverter ac(image);
	ac.setCharSet(createMenu());
	std::cin.get();
	confConsoleColor(uc);
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;
	ac.convertToASCII(); //Converts image to chars and save it in array
	const int HEIGHT = image.getBmpInfo().height - 1;
	for(int i = HEIGHT; i >= 0; i--)
	{
		uc.writeText(ac.getLine(i));
	}
	bmpImages.push_back(image);
}

Controller::~Controller()
{
	std::cout << "Controller " << "destructed" << std::endl;
}
