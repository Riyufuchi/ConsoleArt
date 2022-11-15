//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 15.11.2022
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

Controller::Controller(std::string path)
{
	paths.push_back(path);
}

void Controller::run()
{
	int pathID = 0;
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
	std::cout << "Image name without file extension (only .bmp images):" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	imgName.append(".bmp");
	ImageBMP img((path.append(imgName)).c_str());
	return img;
}

void Controller::linuxVersion(ImageBMP image)
{
	if(image.getFilename() != std::string("NULL"))
	{
		UnixConsole uc;
		AsciiConverter ac(image);
		ac.setCharSet(createMenu());
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
			std::cin.get(); //Catch enter character
		}
		//Explicit outputting of converted image
		const int height = image.getBmpInfo().height;
		for(int i = 0; i < height; i++)
		{
			uc.writeText(ac.getLine(i));
		}
		//Implicit: img.outputAsciiImage();
	}
}

Controller::~Controller()
{
}
