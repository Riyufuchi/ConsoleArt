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
			std::string path = reinterpret_cast<const char*>((argv[i + 1])); //or std::string path{argv[2]};
			if((path.substr(path.length() - 1) != "/") && (path.length() > 0)) //if(argv[2][path.length() - 1] == '/')
				path.append("/");
			workspacePath = path;
			std::cout << "Workspace path: " << workspacePath << std::endl;
		}
		else if (!strcmp(argv[i], "--loadAll"))
		{
			loadAllImages();
		}
	}
}

void Controller::loadAllImages()
{
	try
	{
		std::filesystem::current_path(workspacePath);
		for (const auto& entry : std::filesystem::directory_iterator("."))
		{
			addImage(std::unique_ptr<Images::Image>(new Images::ImageBMP(workspacePath + entry.path().generic_string().substr(2))));
			//images.push_back(new Images::ImageBMP(workspacePath + entry.path().generic_string().substr(2)));
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void Controller::run()
{
	menu: do
	{
		switch(MenuUtils::actionMenu())
		{
			case 0: linuxVersion(loadImage(workspacePath)); break;
			case 1: linuxVersion(selectImage()); /* images.erase(images.begin() + 12);*/ break;
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

Images::Image* Controller::selectImage()
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
	return images[selectedIndex].get();
	/*
	if (auto bmpImagePtr = dynamic_cast<Images::ImageBMP*>(images[selectedIndex].get()))
	{
		return *bmpImagePtr;
	}
	else
	{
		unxConsole.writeText(255, 0, 0, "Selected image is not of type ImageBMP!");
		return Images::ImageBMP("nullPtr.bmp");
	}*/
}

Images::Image* Controller::loadImage(std::string path)
{
	std::cout << "Image name without file extension - only bitmap (.bmp) images:" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); //Clears enter from console
	return new Images::ImageBMP (path + imgName.append(".bmp"));
}

void Controller::confConsoleColor()
{
	if (ConsoleUtils::ConsoleUtility::yesNo("Select color [Y/n]: "))
	{
		int max = ConsoleUtils::Colors::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			std::cout << i << ". ";
			unxConsole.writeText(ConsoleUtils::Colors::getColor(static_cast<ConsoleUtils::Colors::ColorPallete>(i)), ConsoleUtils::Colors::colorPaletteNames[i]);
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

void Controller::addImage(std::unique_ptr<Images::Image> image)
{
	if (image == nullptr)
		return;
	if(!images.empty())
	{
		int maxIndex = images.size();
		for(int i = 0; i < maxIndex; i++)
			if(images[i]->getFilename() == image->getFilename())
				return;
	}
	images.push_back(std::move(image));
}

void Controller::linuxVersion(Images::Image* image)
{
	if (image == nullptr || !image) //if (!image.isLoaded())
		return;
	ImageUtils::AsciiConverter ac(image);
	ac.setCharSet(MenuUtils::charSetMenu());
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;
	ac.convertToASCII();
	const int HEIGHT = image->getImageInfo().height - 1;
	for(int i = HEIGHT; i >= 0; i--)
	{
		unxConsole.writeText(ac.getLine(i));
	}
}

Controller::~Controller()
{
	//for(size_t i = 0; i < images.size(); i++)
		//delete images[i];
	std::cout << "Controller " << "destructed" << std::endl;
}
}
