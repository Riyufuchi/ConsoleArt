//============================================================================
// Name        : UnixControllerCLI.cpp
// Author      : Riyufuchi
// Created on  : 18.12.2023
// Last Edit   : 18.12.2023
// Description : This class is CLI controller for the main app
//============================================================================

#include "ControllerCLI.h"

namespace ConsoleArt
{
ControllerCLI::ControllerCLI(ConsoleUtils::IConsole& console) : ControllerCLI("", console)
{
}

ControllerCLI::ControllerCLI(std::string path, ConsoleUtils::IConsole& console) : Controller(path), console(console)
{

}
/*std::string command = "cd ";
command += workspacePath;
command += " && ";
command += "ls";
system(command.c_str());*/
void ControllerCLI::run()
{
	menu:
	switch(MenuUtils::actionMenu())
	{
		case 0:
			if (addImage(loadImage(workspacePath + inputImageName())))
				convertImage(images.back().get());
			goto menu;
		case 1: loadAllImages(); goto menu;
		case 2: convertImage(selectImage()); goto menu;
		case 3: ConsoleUtils::ConsoleUtility::listFilesInFolder(workspacePath); goto menu;
		case 4: confConsoleColor(); goto menu;
		case 5: return;
	}
}

Images::Image* ControllerCLI::selectImage()
{
	if(images.empty())
	{
		console.out(255, 255, 0, "No images were loaded yet!\n");
		return 0;
	}
	std::cout << "Currently loaded images:" << std::endl;
	int max = images.size();
	for(int index = 0; index < max; index++) // or for(Images::Image* img : images)
	{
		std::cout << index + 1 << ". " << images[index]->getFilename() << std::endl;
	}

	int selectedIndex = ConsoleUtils::ConsoleUtility::getIntSafe(1, max) - 1;
	ImageUtils::ImageToolsCLI::displayImageInfo(images[selectedIndex].get());
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

std::string ControllerCLI::inputImageName()
{
	std::cout << "Image name with file extension: ";
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); //Clears enter from console
	return imgName;
}

void ControllerCLI::confConsoleColor()
{
	if (ConsoleUtils::ConsoleUtility::yesNo("Select color [Y/n]: "))
	{
		int max = ConsoleUtils::ColorUtils::ColorPallete::COLOR_COUNT;
		for (int i = 0; i < max; ++i)
		{
			std::cout << i + 1 << ". ";
			console.out(ConsoleUtils::ColorUtils::getColor(static_cast<ConsoleUtils::ColorUtils::ColorPallete>(i)), ConsoleUtils::ColorUtils::colorPaletteNames[i]);
			std::cout << "\n";
		}
		((ConsoleUtils::UnixConsole&)console).setDefaultTextColor(ConsoleUtils::ColorUtils::getColor(static_cast<ConsoleUtils::ColorUtils::ColorPallete>(ConsoleUtils::ConsoleUtility::getIntSafe(1, max) - 1)));
	}
	else if(ConsoleUtils::ConsoleUtility::yesNo("Custom color [Y/n]: "))
	{
		std::cout << "Red: ";
		int red = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Green: ";
		int green = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		std::cout << "Blue: ";
		int blue = ConsoleUtils::ConsoleUtility::getIntSafe(0, 255);
		((ConsoleUtils::UnixConsole&)console).setDefaultTextColor(ConsoleUtils::ColorUtils::newColor(red, green, blue));
	}
}

void ControllerCLI::convertImage(Images::Image* image)
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
	std::cout << "Processing image:" << std::endl;
	ImageUtils::ImageToolsCLI::displayImageInfo(image);
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	ac.convertToASCII();
	AsciiPrinter ap(ac, console, ((ConsoleUtils::UnixConsole&)console).getDefaultTextColor());
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

ControllerCLI::~ControllerCLI()
{
	//for(size_t i = 0; i < images.size(); i++)
		//delete images[i];
	std::cout << "ControllerCLI destructed" << std::endl;
}
}
