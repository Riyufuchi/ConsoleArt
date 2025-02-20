//============================================================================
// Name        : ControllerCLI.cpp
// Author      : Riyufuchi
// Created on  : Dec 18, 2023
// Last Edit   : Feb 18, 2025
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
	constexpr auto checkForArgs = GeneralTools::arguments();
	for (const std::pair<const char*, Argumemts>& argument : checkForArgs)
	{
		if (!config.contains(argument.first))
			continue;
		switch (argument.second)
		{
			case COLOR:
				params = config.at(argument.first);
				if (params.empty() || (!ConsoleLib::DataUtils::isNumber(params.at(0))))
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
				console->out("Text");
			break;
			case CLIENT:
				if (config.at(argument.first).empty())
					runAsClient("");
				else
					runAsClient(config.at(argument.first).at(0));
			break;
			case BENCHMARK: {
				isRunnable = false;
				std::string image = "bench.pcx";
				params = config.at(argument.first);
				if (!params.empty())
					image = params.at(0);
				auto start = std::chrono::steady_clock::now();
				auto end = start;
				Images::Image* img = loadImage(image);
				if (img == nullptr)
					continue;
				ImageUtils::AsciiConverter ac(*img);
				ac.setCharSet(ImageUtils::AsciiConverter::CHAR_SETS::DETAILED_INVERTED);
				ac.convertToASCII();
				end = std::chrono::steady_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
				std::cout << "Benchmark time: " << duration.count() << " ms" << " => " <<  duration.count() / 1000.0 << " seconds" << std::endl;
			} break;
			case BINOM: {
				auto res = Math::MathUtils::binomialDistribution(config.at(argument.first));
				Other::OtherhUtils::printResults<int, long double>(res);
				isRunnable = false;
			} break;
			case LOAD_ALL: loadAllImagesAsync(); break;
			case PATH: setWorkspace(config.at(argument.first).at(0)); break;
			case IMAGE: {
				params = config.at(argument.first);
				if (params.empty())
					messenger->messageUser(Messenger::MessageType::ERROR, "Missing image parameter\n");
				if (params.at(0).find("/") != std::string::npos)
					addImageAsync(loadImage(params.at(0)));
				else
					addImageAsync(loadImage(workspacePath + params.at(0)));
				if (images.size() > 0)
					console->out("Images loaded successfully\n");
			} break;
			case COMPARE: {
				params = config.at(argument.first);
				if (params.size() != 2)
				{
					messenger->messageUser(Messenger::MessageType::ERROR, "Argument " + std::string(argument.first) + " missing " + std::to_string((2 - params.size())) + " parameters!\n");
					continue;
				}
				Images::Image* image1 = loadImage(workspacePath + params.at(0));
				Images::Image* image2 = loadImage(workspacePath + params.at(1));
				if (image1 == nullptr || !*image1)
				{
					messenger->messageUser(Messenger::MessageType::ERROR, "Loading of " + image1->getFilename() + " failed!\n");
					continue;
				}
				if (image2 == nullptr || !*image2)
				{
					messenger->messageUser(Messenger::MessageType::ERROR, "Loading of " + image2->getFilename() + " failed!\n");
					continue;
				}
				switch(ImageUtils::ImageTools::compareImages(*image1, *image2))
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
			} break;
			default:
				messenger->messageUser(Messenger::MessageType::ERROR, GeneralTools::createArgErrorMessage(argument.first));
			break;
		}
	}
}

void ControllerCLI::runAsClient(std::string ip)
{
	isRunnable = false;
	const char* ipAdress = "127.0.0.1";
	if (ip.size() == 0 || ip[0] == '-')
		messenger->messageUser(Messenger::MessageType::INFO, "No server IP address was given, using loop back instead\n");
	else
		ipAdress = ip.c_str();
	ConsoleArt::ClientTools client(*console, ipAdress);
	if (!client.connectClient())
		return;
	client.runClient();
}

void ControllerCLI::refreshMenu()
{
	menuCLI.printMainMenu();
}

void ControllerCLI::imageAction()
{
	switch(menuCLI.invokeMenu(MenusCLI::Menu::IMAGE_ACTION_OPTIONS))
	{
		case 0: convertImage(selectImage()); break;
		case 1:
		{
			console->out("Select image:\n");
			Images::Image* image = selectImage();
			if (image == nullptr || !*image)
				return;
			console->out("Select signature:\n");
			Images::Image* image2 = selectImage();
			if (image2 == nullptr || !*image2)
				return;
			ImageUtils::ImageTools::signatureToImage(*image, *image2);
		}
		break;
		case 2:
		{
			Images::Image* image = selectImage();
			if (image == nullptr)
				return;
			if (ImageUtils::Filter::matrixFilter(*image))
				console->out("Matrix filer successfully applied.");
		}
		break;
	}
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
		case 0: addImageAsync(loadImage(inputImageName())); goto menu;
		case 1: loadAllImagesAsync(); goto menu;
		case 2: imageAction(); goto menu;
		case 3:
			console->enableCustomFG();
			ConsoleLib::ConsoleUtils::listFilesInFolder(workspacePath);
			console->disableCustomFG();
			goto menu;
		case 4: menuCLI.invokeMenu(MenusCLI::COLOR_PICKER); goto menu;
		case 5:
			console->enableCustomFG();
			GeneralTools::aboutApplication();
			console->disableCustomFG();
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
	if (images.empty())
	{
		console->out(warningColor, "No images has been loaded yet!\n");
		return 0;
	}
	console->enableCustomFG();
	std::cout << "Currently loaded images (0 to exit):" << std::endl;
	int max = images.size();
	for (int index = 0; index < max; index++) // or for(Images::Image* img : images)
	{
		std::cout << index + 1 << ". " << images[index]->getFilename() << std::endl;
	}

	int selectedIndex = ConsoleLib::ConsoleUtils::getIntSafe(0, max) - 1;
	if (selectedIndex == -1)
		return nullptr;
	std::cout << "\n";
	messenger->displayImageInfo(*images[selectedIndex].get());
	std::cout << "\n";
	console->disableCustomFG();
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
	if (image == nullptr || !*image)
		return;
	messenger->messageUser(Messenger::MessageType::INFO, "Processing image:\n");
	messenger->displayImageInfo(*image);
	messenger->messageUser(Messenger::MessageType::NOTIFICATION, "Press Enter to continue...");
	std::cin.get();
	std::cout << "\n";
	ImageUtils::AsciiConverter ac(*image);
	reconvert: int option = menuCLI.invokeMenu(MenusCLI::Menu::CHAR_SET_SELECTION);
	if (option == ImageUtils::AsciiConverter::CHAR_SETS::CHAR_SETS_COUNT)
		return;
	ac.setCharSet(option);
	console->enableCustomFG();
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
			case 4: goto reconvert;
			case 5: again = false; break;
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
