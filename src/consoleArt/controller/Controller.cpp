//============================================================================
// Name        : Controller.cpp
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Feb 17, 2025
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

namespace ConsoleArt
{
Controller::Controller() : Controller("") // Calls constructor with parameter to construct class
{
}
Controller::Controller(std::string path) : workspacePath(path), isRunnable(true), messenger(nullptr), selectedImage(nullptr)
{
	suppertedImageFormats[".pcx"] = Format::PCX;
	suppertedImageFormats[".bmp"] = Format::BMP;
	suppertedImageFormats[".ppm"] = Format::PPM;
	suppertedImageFormats[".png"] = Format::PNG;
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
		messenger->messageUser(Messenger::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	std::sort(images.begin(), images.end(), [](const std::unique_ptr<Images::Image>& a, const std::unique_ptr<Images::Image>& b)
	{
		return a->getFilename() < b->getFilename();
	});
	messenger->messageUser(Messenger::MessageType::SUCCESFUL_TASK, "All loaded!\a\n");
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
	messenger->messageUser(Messenger::MessageType::WARNING, "Unsupported format \"" + extension + "\"\n");
	return nullptr;
}
bool Controller::addImageAsync(Images::Image* image)
{
	if (image == nullptr)
		return false;
	if (!image->isLoaded())
	{
		messenger->messageUser(Messenger::MessageType::ERROR, image->getFileStatus() + "\n");
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

Images::Image* Controller::loadImage(std::string path)
{
	std::string ext = "";
	try
	{
		ext = path.substr(path.find_last_of("."));
	}
	catch (std::exception& e)
	{
		messenger->messageUser(Messenger::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
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
		messenger->messageUser(Messenger::MessageType::WARNING, ext + " is not supported\n");
	return nullptr;
}

void Controller::setWorkspace(std::string path)
{
	if (path.length() == 0)
		return;
	if ((path.length() > 0) && (path.substr(path.length() - 1) != "/"))
		path.append("/");
	workspacePath = path;
	messenger->messageUser(Messenger::MessageType::INFO, "Workspace path: " + workspacePath + "\n");
}

Controller::~Controller()
{
	delete messenger;
	//for(size_t i = 0; i < images.size(); i++)
	//	delete images[i];
	//std::cout << "Controller " << "destructed" << std::endl;
}
}
