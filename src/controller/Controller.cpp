//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 22.11.2022
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

Controller::Controller() : Controller("")
{
}

Controller::Controller(std::string path)
{
	paths.push_back(path);
}

void Controller::configure(int argc, char** argv)
{
	if(!strcmp(argv[1], "-p") || !strcmp(argv[1], "-path"))
	{
		std::string path;//{argv[2]};
		path = reinterpret_cast<const char*>((argv[2]));
		std::cout << "Workspace path: " << path << "\n";
		paths.push_back(path);
	}
}

void Controller::run()
{
	int pathID = paths.size() - 1;
	do
	{
		linuxVersion(loadImage(paths.at(pathID)));
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
	imgName.append(".bmp");
	ImageBMP img((path.append(imgName)).c_str());
	std::cin.get(); //Clears enter from console
	return img;
}

void Controller::linuxVersion(ImageBMP image)
{
	if(!image.isLoaded())
		return;
	UnixConsole uc;
	AsciiConverter ac(image);
	ac.setCharSet(createMenu());
	std::cin.get();
	//img.setCharSet(menuDelegation());
	if (ConsoleUtility::yesNo("Custom color [Y/n]: "))
	{
		std::cout << "Red: ";
		int red = ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Green: ";
		int green = ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Blue: ";
		int blue = ConsoleUtility::getIntSafe(0, 255);
		uc.setTextColor(uc.newColor(red, green, blue));
		std::cin.get(); //Catch enter character
	}
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;
	ac.convertToASCII();
	//img.convertToASCII(); //Converts image to chars and save it in array
	//Explicit outputting of converted image
	const int height = image.getBmpInfo().height;
	for(int i = 0; i < height; i++)
	{
		uc.writeText(ac.getLine(i));
	}
	//Implicit: img.outputAsciiImage();
}

Controller::~Controller()
{
}
