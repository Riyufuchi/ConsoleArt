//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 13.10.2023
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

void Controller::configure(int argc, char** argv)
{
	for(int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-p") || !strcmp(argv[i], "--path"))
		{
			std::string path = reinterpret_cast<const char*>((argv[2])); //or std::string path{argv[2]};
			if((path.substr(path.length() - 1) != "/") && (path.length() > 0)) //if(argv[2][path.length() - 1] == '/')
				path.append("/");
			workspacePath = path;
			std::cout << "Workspace path: " << workspacePath << std::endl;
		}
	}
}

void Controller::run()
{
	menu: do
	{
		switch(MenuUtils::actionMenu())
		{
			case 0: linuxVersion(loadImage(workspacePath)); break;
			case 1: linuxVersion(selectImage()); break;
			case 2: confConsoleColor(); goto menu; break;
			case 3: return;
		}
	}while(ConsoleUtility::repeat());
}

ImageBMP Controller::selectImage()
{
	if(bmpImages.empty())
	{
		unxConsole.writeText(255, 255, 0, "No images are loaded!");
		return loadImage(workspacePath);
	}
	std::cout << "Currently loaded images:" << std::endl;
	int max = bmpImages.size();
	int index = 0;
	for(; index < max; index++) //or for(ImageBMP img : bmpImages)
	{
		std::cout << index + 1 << ". " << bmpImages[index].getFilename() << std::endl;
	}
	return bmpImages.at(ConsoleUtility::getIntSafe(1, bmpImages.size()) - 1);
}

ImageBMP Controller::loadImage(std::string path)
{
	std::cout << "Image name without file extension - only bitmap (.bmp) images:" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); //Clears enter from console
	return ImageBMP (path + imgName.append(".bmp"));
}

void Controller::confConsoleColor()
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
	}
}

void Controller::linuxVersion(ImageBMP image)
{
	if (!image) //if (!image.isLoaded())
		return;
	AsciiConverter ac(image);
	ac.setCharSet(MenuUtils::charSetMenu());
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;
	ac.convertToASCII();
	const int HEIGHT = image.getBmpInfo().height - 1;
	for(int i = HEIGHT; i >= 0; i--)
	{
		unxConsole.writeText(ac.getLine(i));
	}
	if(!bmpImages.empty())
	{
		int maxIndex = bmpImages.size();
		for(int i = 0; i < maxIndex; i++)
			if(bmpImages[i].getFilename() == image.getFilename())
				return;
	}
	bmpImages.push_back(image);
}

Controller::~Controller()
{
	std::cout << "Controller " << "destructed" << std::endl;
}
