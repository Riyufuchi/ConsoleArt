//============================================================================
// Name        : ControllerCLI.cpp
// Author      : Riyufuchi
// Created on  : 18.12.2023
// Last Edit   : 28.12.2023
// Description : This class is CLI controller for the main app
//============================================================================

#include "ControllerCLI.h"

namespace ConsoleArt
{
ControllerCLI::ControllerCLI(ConsoleUtils::IConsole& console) : ControllerCLI("", console)
{
}

ControllerCLI::ControllerCLI(std::string path, ConsoleUtils::IConsole& console) : Controller(path), console(console), menuCLI(MenusCLI(console))
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
	switch(menuCLI.invokeMenu(MenusCLI::Menu::MAIN_MENU))
	{
		case 0:
			if (addImage(loadImage(workspacePath + inputImageName())))
				convertImage(images.back().get());
			goto menu;
		case 1: loadAllImages(); goto menu;
		case 2: convertImage(selectImage()); goto menu;
		case 3:
			console.defaultTextColor();
			ConsoleUtils::ConsoleUtility::listFilesInFolder(workspacePath);
			console.resetTextColor();
			goto menu;
		case 4: menuCLI.invokeMenu(MenusCLI::COLOR_PICKER); goto menu;
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

void ControllerCLI::convertImage(Images::Image* image)
{
	if (image == nullptr)
		return;
	if (!*image) // Why this work only when dereferenced?
		return;
	ImageUtils::AsciiConverter ac(*image);
	int option = menuCLI.invokeMenu(MenusCLI::Menu::CHAR_SET_SELECTION);
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
		switch(menuCLI.invokeMenu(MenusCLI::Menu::PRINT_OPTIONS))
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
