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
Controller::Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter) : workspacePath(path), isRunnable(true), messenger(notifier), menuInterface(menu), abstractAsciiPrinter(asciiPrinter), selectedImage(nullptr)
{
	suppertedImageFormats[".pcx"] = Format::PCX;
	suppertedImageFormats[".bmp"] = Format::BMP;
	suppertedImageFormats[".ppm"] = Format::PPM;
	suppertedImageFormats[".png"] = Format::PNG;
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
void Controller::loadAllImagesAsync()
{
	std::string extension = "";
	std::string itDir = workspacePath;
	if (itDir == "")
		itDir = std::filesystem::current_path().generic_string(); // .generic_string(); is required by Windows
	try
	{
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(itDir))
		{
			extension = entry.path().extension();
			std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
			addImageAsync(loadImageAsync(entry.path(), extension));
		}
	}
	catch (std::runtime_error& e)
	{
		messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	std::sort(images.begin(), images.end(), [](const std::unique_ptr<Images::Image>& a, const std::unique_ptr<Images::Image>& b)
	{
		return a->getFilename() < b->getFilename();
	});
	messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "All loaded!\n");
	refreshMenu();
}
Images::Image* Controller::loadImageAsync(const std::string path, const std::string& extension)
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	if (suppertedImageFormats.contains(extension))
		switch (suppertedImageFormats.at(extension))
		{
			case BMP: return new Images::ImageBMP(path);
			case PCX: return new Images::ImagePCX(path);
			case PPM: return new Images::ImagePPM(path);
			case PNG: return new Images::ImagePNG(path);
			default: return nullptr;
		}
	messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Unsupported format [" + extension + "]\n");
	return nullptr;
}
bool Controller::addImageAsync(Images::Image* image)
{
	if (image == nullptr)
		return false;
	if (!image->isLoaded())
	{
		messenger->messageUser(AbstractNotifier::MessageType::ERROR, image->getFileStatus() + "\n");
		delete image;
		image = NULL;
		return false;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	if (!images.empty())
	{
		for (std::unique_ptr<Images::Image>& existingImage : images)
		{
			if (existingImage->getFilename() == image->getFilename())
			{
				delete image;
				image = NULL;
				return false;
			}
		}
	}
	images.emplace_back(std::unique_ptr<Images::Image>(image));
	return true;
}

Images::Image* Controller::loadImageAsync(const std::string& path)
{
	std::string extension = "";
	try
	{
		extension = path.substr(path.find_last_of("."));
	}
	catch (std::exception& e)
	{
		messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return nullptr;
	}
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	if (suppertedImageFormats.contains(extension))
		switch (suppertedImageFormats.at(extension))
		{
			case BMP: return new Images::ImageBMP(path);
			case PCX: return new Images::ImagePCX(path);
			case PPM: return new Images::ImagePPM(path);
			case PNG: return new Images::ImagePNG(path);
			default: return nullptr;
		}
	messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Unsupported format \"" + extension + "\"\n");
	return nullptr;
}

Images::Image* Controller::loadImage(std::string path)
{
	std::string ext = "";
	try
	{
		ext = path.substr(path.find_last_of("."));
	}
	catch (std::exception& e)
	{
		messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return nullptr;
	}
	if (ext == ".pcx")
		return new Images::ImagePCX(path);
	else if (ext == ".bmp")
		return new Images::ImageBMP(path);
	else if (ext == ".ppm")
		return new Images::ImagePPM(path);
	else if (ext == ".png")
		return new Images::ImagePNG(path);
	else
		messenger->messageUser(AbstractNotifier::MessageType::WARNING, ext + " is not supported\n");
	return nullptr;
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

void Controller::setWorkspace(std::string path)
{
	if (path.length() == 0)
		return;
	if ((path.length() > 0) && (path.substr(path.length() - 1) != "/"))
		path.append("/");
	workspacePath = path;
	messenger->messageUser(AbstractNotifier::MessageType::INFO, "Workspace path: " + workspacePath + "\n");
}
}
