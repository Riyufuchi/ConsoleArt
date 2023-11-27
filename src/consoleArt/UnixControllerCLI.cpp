//============================================================================
// Name        : UnixControllerCLI.cpp
// Author      : Riyufuchi
// Created on  : 22.11.2023
// Last Edit   : 27.11.2023
// Description : This class is Unix CLI controller for the main app
//============================================================================

#include "UnixControllerCLI.h"

namespace ConsoleArt
{
UnixControllerCLI::UnixControllerCLI() : UnixControllerCLI("") //Calls constructor with parameter to construct class
{
}

UnixControllerCLI::UnixControllerCLI(std::string path) : Controller(path, unixConsole)
{
}

void UnixControllerCLI::loadAllImages()
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

/*std::string command = "cd ";
command += workspacePath;
command += " && ";
command += "ls";
system(command.c_str());*/
void UnixControllerCLI::run()
{
	menu:
	switch(MenuUtils::actionMenu())
	{
		case 0:
			addImage(std::unique_ptr<Images::Image>(loadImage(workspacePath + inputImageName())));
			convertImage(images.back().get()); goto menu;
		case 1: loadAllImages(); goto menu;
		case 2: convertImage(selectImage()); goto menu;
		case 3: ConsoleUtils::ConsoleUtility::listFilesInFolder(workspacePath); goto menu;
		case 4: confConsoleColor(); goto menu;
		case 5: return;
	}
}

Images::Image* UnixControllerCLI::selectImage()
{
	if(images.empty())
	{
		unixConsole.writeTextLine(255, 255, 0, "No images were loaded yet!");
		return 0;
	}
	std::cout << "Currently loaded images:" << std::endl;
	int max = images.size();
	for(int index = 0; index < max; index++) // or for(Images::Image* img : images)
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

std::string UnixControllerCLI::inputImageName()
{
	std::cout << "Image name without file extension - only bitmap (.bmp) images:" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); //Clears enter from console
	return imgName.append(".bmp");
}

Images::Image* UnixControllerCLI::loadImage(std::string path)
{
	return new Images::ImageBMP(path);
}

void UnixControllerCLI::confConsoleColor()
{
	if (ConsoleUtils::ConsoleUtility::yesNo("Select color [Y/n]: "))
	{
		int max = ConsoleUtils::Colors::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			std::cout << i + 1 << ". ";
			unixConsole.writeTextLine(ConsoleUtils::Colors::getColor(static_cast<ConsoleUtils::Colors::ColorPallete>(i)), ConsoleUtils::Colors::colorPaletteNames[i]);
		}
		unixConsole.setDefaultTextColor(ConsoleUtils::Colors::getColor(static_cast<ConsoleUtils::Colors::ColorPallete>(ConsoleUtils::ConsoleUtility::getIntSafe(1, max) - 1)));
	}
	else if(ConsoleUtils::ConsoleUtility::yesNo("Custom color [Y/n]: "))
	{
		std::cout << "Red: ";
		int red = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Green: ";
		int green = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Blue: ";
		int blue = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		unixConsole.setDefaultTextColor(ConsoleUtils::Colors::newColor(red, green, blue));
	}
}

void UnixControllerCLI::convertImage(Images::Image* image)
{
	if (image == nullptr)
		return;
	if (!*image) // Why this work only when dereferenced?
		return;
	ImageUtils::AsciiConverter ac(*image);
	int option = MenuUtils::charSetMenu();
	if (option == ImageUtils::AsciiConverter::CHAR_SETS::CHAR_SETS_COUNT)
		return;
	ac.setCharSet(option);
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;
	ac.convertToASCII();
	AsciiPrinter ap(ac, unixConsole, unixConsole.getDefaultTextColor());
	bool again = true;
	while (again)
	{
		switch(MenuUtils::printMenu())
		{
			case 0: ap.printClassic(); break;
			case 1: ap.printCharColored(); break;
			case 2: ap.printPixelColored(); break;
			case 3: ap.printToFile(); break;
			case 4: again = false; break;
		}
	}
}

UnixControllerCLI::~UnixControllerCLI()
{
	//for(size_t i = 0; i < images.size(); i++)
		//delete images[i];
	std::cout << "UnixControllerCLI destructed" << std::endl;
}
}
