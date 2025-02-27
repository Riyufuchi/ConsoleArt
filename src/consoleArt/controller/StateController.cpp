//==============================================================================
// File       : StateController.cpp
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "StateController.h"

namespace ConsoleArt {

StateController::StateController(std::string workspace) : workspacePath(workspace)
{
	suppertedImageFormats[".pcx"] = Images::ImageType::PCX;
	suppertedImageFormats[".bmp"] = Images::ImageType::BMP;
	suppertedImageFormats[".ppm"] = Images::ImageType::PPM;
	suppertedImageFormats[".png"] = Images::ImageType::PNG;
}

StateController::~StateController()
{
}

void StateController::loadAllImagesAsync()
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
		//messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	std::sort(images.begin(), images.end(), [](const std::unique_ptr<Images::Image>& a, const std::unique_ptr<Images::Image>& b)
	{
		return a->getFilename() < b->getFilename();
	});
	//messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "All loaded!\n");
	//refreshMenu();
}

bool StateController::addImageAsync(Images::Image* image)
{
	if (image == nullptr)
		return false;
	if (!image->isLoaded())
	{
		//messenger->messageUser(AbstractNotifier::MessageType::ERROR, image->getFileStatus() + "\n");
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

Images::Image* StateController::loadImage(std::string path)
{
	std::string ext = "";
	try
	{
		ext = path.substr(path.find_last_of("."));
	}
	catch (std::exception& e)
	{
		//messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
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
		//messenger->messageUser(AbstractNotifier::MessageType::WARNING, ext + " is not supported\n");
	return nullptr;
}

Images::Image* StateController::loadImageAsync(const std::string& path)
{
	std::string extension = "";
	try
	{
		extension = path.substr(path.find_last_of("."));
	}
	catch (std::exception& e)
	{
		//messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return nullptr;
	}
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	if (suppertedImageFormats.contains(extension))
		switch (suppertedImageFormats.at(extension))
		{
			case Images::BMP: return new Images::ImageBMP(path);
			case Images::PCX: return new Images::ImagePCX(path);
			case Images::PPM: return new Images::ImagePPM(path);
			case Images::PNG: return new Images::ImagePNG(path);
			default: return nullptr;
		}
	//messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Unsupported format \"" + extension + "\"\n");
	return nullptr;
}

Images::Image* StateController::loadImageAsync(const std::string path, const std::string& extension)
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	if (suppertedImageFormats.contains(extension))
		switch (suppertedImageFormats.at(extension))
		{
			case Images::BMP: return new Images::ImageBMP(path);
			case Images::PCX: return new Images::ImagePCX(path);
			case Images::PPM: return new Images::ImagePPM(path);
			case Images::PNG: return new Images::ImagePNG(path);
			default: return nullptr;
		}
	//messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Unsupported format [" + extension + "]\n");
	return nullptr;
}

void StateController::setWorkspace(std::string path)
{
	if (path.length() == 0)
		return;
	if ((path.length() > 0) && (path.substr(path.length() - 1) != "/"))
		path.append("/");
	workspacePath = path;
	//messenger->messageUser(AbstractNotifier::MessageType::INFO, "Workspace path: " + workspacePath + "\n");
}

const std::string& StateController::getWorkspace()
{
	return workspacePath;
}

const std::vector<std::unique_ptr<Images::Image>>& StateController::getImages()
{
	return images;
}

} /* namespace ConsoleArt */
