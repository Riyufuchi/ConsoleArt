//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 21.11.2023
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

namespace ConsoleArt
{
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
			case 2: {
				/*std::string command = "cd ";
				command += workspacePath;
				command += " && ";
				command += "ls";
				system(command.c_str());*/
				ConsoleUtils::ConsoleUtility::listFilesInFolder(workspacePath);
			}
				goto menu;
				break;
			case 3: confConsoleColor(); goto menu; break;
			case 4: return;
		}
	}while(ConsoleUtils::ConsoleUtility::repeat());
}

Images::ImageBMP Controller::selectImage()
{
	if(images.empty())
	{
		unxConsole.writeText(255, 255, 0, "No images are loaded!");
		return loadImage(workspacePath);
	}
	std::cout << "Currently loaded images:" << std::endl;
	int max = images.size();
	for(int index = 0; index < max; index++) //or for(ImageBMP img : bmpImages)
	{
		std::cout << index + 1 << ". " << images[index]->getFilename() << std::endl;
	}

	int selectedIndex = ConsoleUtils::ConsoleUtility::getIntSafe(1, max) - 1;
	Images::Image* selectedImageBase = images[selectedIndex];

	if (auto bmpImage = dynamic_cast<Images::ImageBMP*>(selectedImageBase))
	{
		return *bmpImage;
	}
	else
	{
		unxConsole.writeText(255, 0, 0, "Selected image is not of type ImageBMP!");
		return Images::ImageBMP("nullPtr.bmp");
	}
}

Images::ImageBMP Controller::loadImage(std::string path)
{
	std::cout << "Image name without file extension - only bitmap (.bmp) images:" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); //Clears enter from console
	return Images::ImageBMP (path + imgName.append(".bmp"));
}

void Controller::confConsoleColor()
{
	if (ConsoleUtils::ConsoleUtility::yesNo("Select color [Y/n]: "))
	{
		const char* colorPalleteNames[] = {
			"HAUNTED",
			"UNIQUE",
			"STRANGE",
			"UNUSUAL",
			"COLLECTORS",
			"VALVE_VIOLET",
			"COMMUNITY"
		};
		int max = ConsoleUtils::Colors::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			std::cout << i << ". ";
			unxConsole.writeText(ConsoleUtils::Colors::getColor(static_cast<ConsoleUtils::Colors::ColorPallete>(i)), colorPalleteNames[i]);
		}
		unxConsole.setTextColor(ConsoleUtils::Colors::getColor(static_cast<ConsoleUtils::Colors::ColorPallete>(ConsoleUtils::ConsoleUtility::getIntSafe(0, max - 1))));
	}
	else if(ConsoleUtils::ConsoleUtility::yesNo("Custom color [Y/n]: "))
	{
		std::cout << "Red: ";
		int red = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Green: ";
		int green = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Blue: ";
		int blue = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		unxConsole.setTextColor(ConsoleUtils::Colors::newColor(red, green, blue));
	}
}

void Controller::linuxVersion(Images::ImageBMP image)
{
	if (!image) //if (!image.isLoaded())
		return;
	ImageUtils::AsciiConverter ac(image);
	ac.setCharSet(MenuUtils::charSetMenu());
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;
	ac.convertToASCII();
	const int HEIGHT = image.getImageInfo().height - 1;
	for(int i = HEIGHT; i >= 0; i--)
	{
		unxConsole.writeText(ac.getLine(i));
	}
	if(!images.empty())
	{
		int maxIndex = images.size();
		for(int i = 0; i < maxIndex; i++)
			if(images[i]->getFilename() == image.getFilename())
				return;
	}
	images.push_back(new Images::ImageBMP((image)));
}

Controller::~Controller()
{
	std::cout << "Controller " << "destructed" << std::endl;
}
}
