//============================================================================
// Name        : ControllerCLI.cpp
// Author      : Riyufuchi
// Created on  : Dec 18, 2023
// Last Edit   : Feb 24, 2025
// Description : This class is CLI controller for the main app
//============================================================================

#include "ControllerCLI.h"

namespace ConsoleArt
{
ControllerCLI::ControllerCLI(ConsoleLib::IConsole* console) : ControllerCLI("", console)
{
}
ControllerCLI::ControllerCLI(std::string path, ConsoleLib::IConsole* console) : Controller(path, new NotifierCLI(console), new MenuCLI(console), new AsciiPrinterCLI(console ? *console : defaultConsole)), console(console)
{
	if (console == nullptr)
	{
		this->console = &defaultConsole;
		((MenuCLI*)menuInterface)->setConsole(this->console);
	}
	((NotifierCLI*)messenger)->setConsole(console);
}
ControllerCLI::~ControllerCLI()
{
	std::cout << "ControllerCLI destructed\n";
}
void ControllerCLI::configure(std::map<std::string, std::vector<std::string>>& config)
{
	/*
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
					messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Missing or wrong argument " + params.at(0) + " for --color\n");
					continue;
				}
				console->setDefaultTextColor(ConsoleLib::ColorUtils::getColor(static_cast<ConsoleLib::ColorPallete>(std::stoi(params.at(0)) - 1)));
			break;
			case NO_COLOR:
				this->console = &defaultConsole;
				((MenuCLI*)menuInterface)->setConsole(console);
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
					messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Missing image parameter\n");
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
					messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Argument " + std::string(argument.first) + " missing " + std::to_string((2 - params.size())) + " parameters!\n");
					continue;
				}
				Images::Image* image1 = loadImage(workspacePath + params.at(0));
				Images::Image* image2 = loadImage(workspacePath + params.at(1));
				if (image1 == nullptr || !*image1)
				{
					messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Loading of " + image1->getFilename() + " failed!\n");
					continue;
				}
				if (image2 == nullptr || !*image2)
				{
					messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Loading of " + image2->getFilename() + " failed!\n");
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
				messenger->messageUser(AbstractNotifier::MessageType::ERROR, GeneralTools::createArgErrorMessage(argument.first));
			break;
		}
	}*/
}

void ControllerCLI::runAsClient(std::string ip)
{
	isRunnable = false;
	const char* ipAdress = "127.0.0.1";
	if (ip.size() == 0 || ip[0] == '-')
		messenger->messageUser(AbstractNotifier::MessageType::INFO, "No server IP address was given, using loop back instead\n");
	else
		ipAdress = ip.c_str();
	ConsoleArt::ClientTools client(*console, ipAdress);
	if (!client.connectClient())
		return;
	client.runClient();
}

void ControllerCLI::refreshMenu()
{
	((MenuCLI*)menuInterface)->printMainMenu();
}

void ControllerCLI::imageAction()
{
	if (selectedImage == nullptr)
	{
		messenger->messageUser(AbstractNotifier::MessageType::WARNING, "No image is selected!\n");
		return;
	}
	switch(menuInterface->imageEditOptions())
	{
		case 0: convertImage(selectedImage); break;
		case 1:
		{
			console->out("Select signature:\n");
			Images::Image* image = 0;//selectImage();
			if (image == nullptr || !*image)
				return;
			ImageUtils::ImageTools::signatureToImage(*selectedImage, *image);
		}
		break;
		case 2:
		{
			bool res = false;
			switch (menuInterface->imageFilterOptions())
			{
				case 0: res = ImageUtils::Filter::matrixFilter(*selectedImage); break;
				case 1: res = ImageUtils::Filter::purplefier(*selectedImage); break;
				case 2: res = ImageUtils::Filter::purplefierSoft(*selectedImage); break;
				case 3: res = ImageUtils::Filter::purplefierShading(*selectedImage); break;
				case 4: res = ImageUtils::Filter::purplefierShadingSoft(*selectedImage); break;
			}
			if (res)
				messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "Filer successfully applied.\n");
			else
				messenger->messageUser(AbstractNotifier::MessageType::ERROR, "An error occurred while applying filter to image " + selectedImage->getFilename() + "\n");
		}
		break;
	}
}
/*
void ControllerCLI::showAboutApplicationInfo()
{
	console->out(GeneralTools::aboutApplication());
}
*/
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
	Images::Image* imageHolder = nullptr;
	menu:
	console->out("Selected image: ");
	if (selectedImage != nullptr)
		console->out(selectedImage->getFilename());
	else
		console->out("None");
	std::cout << "\n";
	switch(((MenuCLI*)menuInterface)->printMainMenu())
	{
		case 0: /*addImageAsync(loadImage(inputImageName())); */goto menu;
		case 1: loadAllImagesAsync(); goto menu;
		case 2:
			/*imageHolder = selectImage();
			if (imageHolder != nullptr)
				selectedImage = imageHolder;*/
		goto menu;
		case 3: imageAction(); goto menu;
		case 4:
			console->enableCustomFG();
			ConsoleLib::ConsoleUtils::listFilesInFolder(stateController.getWorkspace());
			console->disableCustomFG();
			goto menu;
		case 5: ((MenuCLI*)menuInterface)->confConsoleTextColor(); goto menu;
		case 6: /*showAboutApplicationInfo(); */ goto menu;
		case 7: return;
	}
}

void ControllerCLI::loadAllImagesAsync()
{
	std::thread thread([this]()
	{
		stateController.loadAllImagesAsync();
	});
	thread.detach();
}
/*
Images::Image* ControllerCLI::selectImage()
{
	if (stateController.getImages().empty())
	{
		console->out(warningColor, "No images has been loaded yet!\n");
		return 0;
	}
	console->enableCustomFG();
	std::cout << "Currently loaded images (0 to exit):" << std::endl;
	int max = stateController.getImages().size();
	for (int index = 0; index < max; index++) // or for(Images::Image* img : images)
	{
		std::cout << index + 1 << ". " << stateController.getImages()[index]->getFilename() << std::endl;
	}

	int selectedIndex = ConsoleLib::ConsoleUtils::getIntSafe(0, max) - 1;
	if (selectedIndex == -1)
		return nullptr;
	std::cout << "\n";
	messenger->displayImageInfo(*stateController.getImages()[selectedIndex].get());
	std::cout << "\n";
	console->disableCustomFG();
	return stateController.getImages()[selectedIndex].get();
}

std::string ControllerCLI::inputImageName()
{
	std::cout << "Image name with file extension: ";
	std::string imgName;
	std::cin >> imgName;
	std::cin.get(); // Clears enter from console
	return stateController.getWorkspace() + imgName;
}*/
}
