//============================================================================
// Name        : ControllerCLI.cpp
// Author      : Riyufuchi
// Created on  : Dec 18, 2023
// Last Edit   : Jan 20, 2025
// Description : This class is CLI controller for the main app
//============================================================================

#include "ControllerCLI.h"

namespace ConsoleArt
{
ControllerCLI::ControllerCLI(ConsoleLib::IConsole* console) : ControllerCLI("", console)
{
}
ControllerCLI::ControllerCLI(std::string path, ConsoleLib::IConsole* console) : Controller(path), console(console), menuCLI(MenusCLI(console))
{
	if (console == nullptr)
	{
		this->console = &defaultConsole;
		menuCLI.setConsole(this->console);
	}
	messenger = new MessengerCLI(this->console);
}
void ControllerCLI::configure(std::map<std::string, std::vector<std::string>>& config)
{
	std::vector<std::string> params;
	std::vector<std::pair<std::string, Argumemts>> checkForArgs = GeneralTools::arguments();
	for (std::pair<std::string, Argumemts> argument : checkForArgs)
	{
		if (!config.contains(argument.first))
			continue;
		switch (argument.second)
		{
			case COLOR:
				params = config.at(argument.first);
				if (params.empty() || (!DataUtility::DataUtils::isNumber(params.at(0))))
				{
					messenger->messageUser(Messenger::MessageType::ERROR, "Missing or wrong argument " + params.at(0) + " for --color\n");
					continue;
				}
				console->setDefaultTextColor(ConsoleLib::ColorUtils::getColor(static_cast<ConsoleLib::ColorPallete>(std::stoi(params.at(0)) - 1)));
			break;
			case NO_COLOR:
				this->console = &defaultConsole;
				menuCLI.setConsole(console);
				console->out("No color option applied\n");
			break;
			case CLIENT:
				if (!config.at(argument.first).empty())
					runAsClient(config.at(argument.first).at(0));
			break;
			case SCHEDULE: {
				Other::ScheduleTracker shedule(console);
				shedule.menu();
				isRunnable = false;
			} break;
			case BENCHMARK: {
				std::string image = "bench.pcx";
				params = config.at(argument.first);
				if (!((params.empty() || params.at(0)[0] == '-')))
					image = params.at(0);
				auto start = std::chrono::steady_clock::now();
				auto end = start;
				Images::Image* img = loadImage(image);
				ImageUtils::AsciiConverter ac(*img);
				ac.setCharSet(ImageUtils::AsciiConverter::CHAR_SETS::DETAILED_INVERTED);
				ac.convertToASCII();
				end = std::chrono::steady_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
				std::cout << "Benchmark time: " << duration.count() << " ms" << " => " <<  duration.count() / 1000.0 << " seconds" << std::endl;
				isRunnable = false;
			} break;
			case BINOM: {
				Other::OtherhUtils::distributeCards();
				std::cout << "\n";
				Other::OtherhUtils::testMean();
				isRunnable = false;
			} break;
			case LOAD_ALL: loadAllImagesAsync(); break;
			case PATH: setWorkspace(config.at(argument.first).at(0)); break;
			case IMAGE: {
				params = config.at(argument.first);
				if (params.empty())
					messenger->messageUser(Messenger::MessageType::ERROR, "Missing image parameter\n");
				addImage(loadImage(workspacePath + params.at(0)));
				if (images.size() > 0)
					convertImage(images.back().get());
			} break;
			default:
				messenger->messageUser(Messenger::MessageType::ERROR, GeneralTools::createArgErrorMessage(argument.first));
			break;
		}
	}
}

void ControllerCLI::runAsClient(std::string ip)
{
	const char* ipAdress = "127.0.0.1";
	if (ip[0] == '-')
		messenger->messageUser(Messenger::MessageType::INFO, "No server IP address was given, using loop back instead\n");
	else
		ipAdress = ip.c_str();
	ConsoleArt::ClientTools client(*console, ipAdress);
	if (client.runClient())
		isRunnable = false;
}

void ControllerCLI::refreshMenu()
{
	menuCLI.printMainMenu();
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
		if(ConsoleLib::ConsoleUtils::yesNo("Exit application? [Y/n]"))
			return;
	}
	menu:
	switch(menuCLI.invokeMenu(MenusCLI::Menu::MAIN_MENU))
	{
		case 0:
			if (addImage(loadImage(inputImageName())))
				convertImage(images.back().get());
			goto menu;
		case 1: loadAllImagesAsync(); goto menu;
		case 2: convertImage(selectImage()); goto menu;
		case 3:
			console->defaultTextColor();
			ConsoleLib::ConsoleUtils::listFilesInFolder(workspacePath);
			console->resetTextColor();
			goto menu;
		case 4: menuCLI.invokeMenu(MenusCLI::COLOR_PICKER); goto menu;
		case 5:
			console->defaultTextColor();
			GeneralTools::aboutApplication();
			console->resetTextColor();
		goto menu;
		case 6: return;
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

Images::Image* ControllerCLI::selectImage()
{
	if(images.empty())
	{
		console->out(255, 255, 0, "No images has been loaded yet!\n");
		return 0;
	}
	console->defaultTextColor();
	std::cout << "Currently loaded images:" << std::endl;
	int max = images.size();
	for(int index = 0; index < max; index++) // or for(Images::Image* img : images)
	{
		std::cout << index + 1 << ". " << images[index]->getFilename() << std::endl;
	}

	int selectedIndex = ConsoleLib::ConsoleUtils::getIntSafe(1, max) - 1;
	std::cout << "\n";
	ImageUtils::ImageToolsCLI::displayImageInfo(images[selectedIndex].get());
	std::cout << "\n";
	console->resetTextColor();
	return images[selectedIndex].get();
}

std::string ControllerCLI::inputImageName()
{
	std::cout << "Image name with file extension: ";
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); // Clears enter from console
	return workspacePath + imgName;
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
	messenger->messageUser(Messenger::MessageType::INFO, "Processing image:\n");
	menuCLI.displayImageInfo(*image);
	messenger->messageUser(Messenger::MessageType::NOTIFICATION, "Press Enter to continue...");
	std::cin.get();
	console->defaultTextColor();
	if (!ac.convertToASCII())
	{
		messenger->messageUser(Messenger::MessageType::ERROR, "Image conversion has failed!\n");
		return;
	}
	messenger->messageUser(Messenger::MessageType::SUCCESFUL_TASK, "Done!\n");
	AsciiPrinter ap(ac, *console, console->getDefaultTextColor());
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
	std::cout << "ControllerCLI destructed\n";
}
}
