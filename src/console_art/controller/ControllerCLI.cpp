//============================================================================
// Name        : ControllerCLI.cpp
// Author      : Riyufuchi
// Created on  : Dec 18, 2023
// Last Edit   : Dec 23, 2025
// Description : This class is CLI controller for the main app
//============================================================================

#include "../../console_art/controller/ControllerCLI.h"
namespace consoleart
{
ControllerCLI::ControllerCLI(consolelib::IConsole* console) : ControllerCLI("", console)
{
}
ControllerCLI::ControllerCLI(std::string path, consolelib::IConsole* console) : Controller(path, new NotifierCLI(console), new MenuCLI(console), new AsciiPrinterCLI(console ? *console : defaultConsole)), console(console)
{
	if (this->console == nullptr)
	{
		this->console = &defaultConsole;
		((MenuCLI*)menuInterface)->setConsole(this->console);
		((NotifierCLI*)messenger)->setConsole(this->console);
	}
	// Arguments
	argumentMethods["--no-color"] = [&](const auto&)
	{
		this->console = &defaultConsole;
		((MenuCLI*)menuInterface)->setConsole(this->console);
		((NotifierCLI*)messenger)->setConsole(this->console);
		this->console->out("No color option applied\n");
	};
	argumentMethods["--color"] = [&](const auto& vector)
	{
		if (vector.empty() || (!consolelib::data_tools::isNumber(vector.at(0))))
		{
			messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Missing or wrong argument " + vector.at(0) + " for --color\n");
			return;
		}
		int colorID = std::stoi(vector.at(0)) - 1;
		if (colorID >= 0 && colorID < consolelib::ColorPallete::COLOR_COUNT)
			this->console->setDefaultTextColor(consolelib::color_tools::getColor(static_cast<consolelib::ColorPallete>(colorID)));
	};
	argumentMethods["--benchmark"] = [&](const auto& vector) { benchmark(vector); };
	argumentMethods["--compare"] = [&](const auto& vector) { compareImages(vector); };
}
ControllerCLI::~ControllerCLI()
{
	std::cout << "ControllerCLI destroyed\n";
}

void ControllerCLI::benchmark(const std::vector<std::string>& vector)
{
	isRunnable = false;
	std::string image = "bench.pcx";
	if (!vector.empty())
		image = vector.at(0);
	auto start = std::chrono::steady_clock::now();
	auto end = start;
	consoleartlib::Image* img = loadImageAsync(image);
	if (img == nullptr)
		return;
	consoleartlib::AsciiConverter ac(*img);
	ac.setCharSet(consoleartlib::AsciiConverter::CHAR_SETS::DETAILED_INVERTED);
	ac.convertToASCII();
	end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Benchmark time: " << duration.count() << " ms" << " => " <<  duration.count() / 1000.0 << " seconds" << std::endl;
}

void ControllerCLI::compareImages(const std::vector<std::string>& vector)
{
	if (vector.size() != 2)
	{
		messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Argument --compare is missing " + std::to_string((2 - vector.size())) + " parameters!\n");
		return;
	}
	consoleartlib::Image* image1 = loadImageAsync(workspacePath + vector.at(0));
	consoleartlib::Image* image2 = loadImageAsync(workspacePath + vector.at(1));
	if (image1 == nullptr || !*image1)
	{
		messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Loading of " + image1->getFilename() + " failed!\n");
		return;
	}
	if (image2 == nullptr || !*image2)
	{
		messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Loading of " + image2->getFilename() + " failed!\n");
		return;
	}
	switch(consoleartlib::image_tools::compareImages(*image1, *image2))
	{
		case 1:
			console->out("Image " + image1->getFilename() + " is bigger than " + image2->getFilename() + "\n");
		break;
		case 0:
			console->out("Image " + image1->getFilename() + " is equal to " + image2->getFilename() + "\n");
		break;
		case -1:
			console->out("Image " + image2->getFilename() + " is bigger than " + image1->getFilename() + "\n");
		break;
	}
	isRunnable = false;
}

void ControllerCLI::refreshMenu()
{
	menuInterface->mainMenuOptions();
}

void ControllerCLI::imageActionsSubmenu()
{
	consoleartlib::Image* selectedImage = getSelectedImage();
	if (selectedImage == nullptr)
	{
		messenger->messageUser(AbstractNotifier::MessageType::WARNING, "No image is selected!\n");
		return;
	}
	int option = menuInterface->imageEditOptions();
	switch(option)
	{
		case 0: convertImageToAsciiEvent(); break;
		case 1:
		{
			console->out("Select signature:\n");
			consoleartlib::Image* image = 0;//selectImage();
			if (image == nullptr || !*image)
				return;
			consoleartlib::image_tools::signatureToImage(*selectedImage, *image);
		}
		break;
		case 2:
		{
			bool res = false;
			option = menuInterface->imageFilterOptions();
			switch (option)
			{
				case 0: res = consoleartlib::filter::matrixFilter(*selectedImage); break;
				case 1: res = consoleartlib::filter::purplefier(*selectedImage); break;
				case 2: res = consoleartlib::filter::purplefierSoft(*selectedImage); break;
				case 3: res = consoleartlib::filter::purplefierShading(*selectedImage); break;
				case 4: res = consoleartlib::filter::purplefierShadingSoft(*selectedImage); break;
				default: messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Invalid filter selection [" + std::to_string(option) + "]\n"); break;
			}
			if (res)
				messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "Filer successfully applied.\n");
			else if (option != -1)
				messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "An error occurred while applying filter to image " + selectedImage->getFilename() + "\n");
		}
		break;
		default:
			if (option == -1)
				messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Invalid image action selection!\n");
		break;
	}
}

void ControllerCLI::showAboutApplicationInfo()
{
	console->out(general_tools::aboutApplication());
}

/*std::string command = "cd ";
command += workspacePath;
command += " && ";
command += "ls";
system(command.c_str());*/
void ControllerCLI::run()
{
	if (!isRunnable)
	{
		if(consolelib::console_tools::yesNo("Exit application? [Y/n]"))
			return;
	}
	IndexDataType lastIndex = 0;
	consoleartlib::Image* selectedImage = nullptr;
	while (isRunnable)
	{
		if (lastIndex != getSelectedImageIndex())
			selectedImage = getSelectedImage();
		console->out("\nSelected image: ");
		if (selectedImage != nullptr)
			console->out(selectedImage->getFilename());
		else
			console->out("None");
		std::cout << "\n\n";
		switch(menuInterface->mainMenuOptions())
		{
			case 0: loadImageEvent(); break;
			case 1: loadAllImagesAsync(); break;
			case 2: selectImageEvent(); break;
			case 3: imageActionsSubmenu(); break;
			case 4:
				console->enableCustomFG();
				consolelib::console_tools::listFilesInFolder(workspacePath);
				console->disableCustomFG();
				break;
			case 5: ((MenuCLI*)menuInterface)->confConsoleTextColor(); break;
			case 6: showAboutApplicationInfo(); break;
			case 7: isRunnable = false; break;
		}
	}
}

void ControllerCLI::loadAllImagesAsync()
{
	std::thread thread([this]()
	{
		Controller::loadAllImagesAsync();
	});
	thread.detach();
}

Controller::IndexDataType ControllerCLI::selectImageMenu()
{
	if (images.empty())
	{
		console->out(warningColor, "No images has been loaded yet!\n");
		return 0;
	}
	console->enableCustomFG();
	std::cout << "Currently loaded images (0 to exit):" << std::endl;
	int max = images.size();
	for (int index = 0; index < max; index++) // or for(consoleartlib::Image* img : images)
	{
		std::cout << index + 1 << ". " << images[index].imageUptr->getFilename() << std::endl;
	}

	int selectedIndex = consolelib::console_tools::getIntSafe(0, max) - 1;
	if (selectedIndex == -1)
		return 0;
	std::cout << "\n";
	messenger->displayImageInfo(*images[selectedIndex].imageUptr.get());
	std::cout << "\n";
	console->disableCustomFG();
	return images[selectedIndex].index;
}

std::string ControllerCLI::inputImageName()
{
	std::cout << "Image name with file extension: ";
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); // Clears enter from console
	return workspacePath + imgName;
}

void ControllerCLI::loadImageEvent()
{
	IndexDataType id = addImageAsync(loadImageAsync(inputImageName()));
	if (id)
		selectImage(id);
}

void ControllerCLI::selectImageEvent()
{
	selectImage(selectImageMenu());
}

void ControllerCLI::convertImageToAsciiEvent()
{
	consoleartlib::Image* selectedImage = getSelectedImage();
	if (selectedImage == nullptr || abstractAsciiPrinter == nullptr)
			return;
	messenger->displayImageInfo(*selectedImage);
	consoleartlib::AsciiConverter ac(*selectedImage);
	int option = 0;
	bool again = true;
	do {
		if (option != -1)
		{
			option = menuInterface->charSetMenu();
			if (option == consoleartlib::AsciiConverter::CHAR_SETS::CHAR_SETS_COUNT)
				return;
			ac.setCharSet(option);
			messenger->messageUser(AbstractNotifier::MessageType::NOTIFICATION, std::string("Started conversion of image: ").append(selectedImage->getFilename()));
			if (!ac.convertToASCII())
			{
				messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Image conversion has failed!\n");
				return;
			}
			messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "Done!\n");
			abstractAsciiPrinter->setTarget(&ac);
		}
		switch(menuInterface->printMenu())
		{
			case 0: abstractAsciiPrinter->printClassic(); break;
			case 1: abstractAsciiPrinter->printCharColored(); break;
			case 2: abstractAsciiPrinter->printPixelColored(); break;
			case 3: abstractAsciiPrinter->printToFile(); break;
			case 4: again = false; break;
		}
		switch(menuInterface->afterPrintOptions())
		{
			case 0: option = 0; break; // Again whole loop
			case 1: option = -1; break; // Just reprint option
			case 2: again = false; break;
		}
	} while (again);
}

}
