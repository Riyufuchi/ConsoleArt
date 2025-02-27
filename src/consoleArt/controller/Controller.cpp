//============================================================================
// Name        : Controller.cpp
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Feb 25, 2025
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

namespace ConsoleArt
{
Controller::Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter) : Controller("", notifier, menu, asciiPrinter)
{
}
Controller::Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter) : stateController(path), isRunnable(true), messenger(notifier), menuInterface(menu), abstractAsciiPrinter(asciiPrinter), selectedImage(nullptr)
{
}
Controller::~Controller()
{
	delete menuInterface;
	delete messenger;
	delete abstractAsciiPrinter;
	//for(size_t i = 0; i < images.size(); i++)
	//	delete images[i];
	std::cout << "Controller " << "destructed" << std::endl;
}

void Controller::convertImage(Images::Image* image)
{
	if (image == nullptr || !*image || abstractAsciiPrinter == nullptr)
		return;
	messenger->displayImageInfo(*image);
	ImageUtils::AsciiConverter ac(*image);
	int option = 0;
	bool again = true;
	do {
		option = menuInterface->charSetMenu();
		if (option == ImageUtils::AsciiConverter::CHAR_SETS::CHAR_SETS_COUNT)
			return;
		ac.setCharSet(option);
		messenger->messageUser(AbstractNotifier::MessageType::NOTIFICATION, std::string("Started conversion of image: ").append(image->getFilename()));
		if (!ac.convertToASCII())
		{
			messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Image conversion has failed!\n");
			return;
		}
		messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "Done!\n");
		abstractAsciiPrinter->setTarget(&ac);
		switch(menuInterface->printMenu())
		{
			case 0: abstractAsciiPrinter->printClassic(); break;
			case 1: abstractAsciiPrinter->printCharColored(); break;
			case 2: abstractAsciiPrinter->printPixelColored(); break;
			case 3: abstractAsciiPrinter->printToFile(); break;
			case 4: break; // Just continue
			case 5: again = false; break;
		}
	} while (again);
}
}
