//============================================================================
// Name        : Controller.cpp
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Mar 20, 2024
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

namespace ConsoleArt
{
Controller::Controller() : Controller("") // Calls constructor with parameter to construct class
{
}
Controller::Controller(std::string path) : workspacePath(path), isRunnable(true)
{
}

bool Controller::applyArgument(int argc, char** argv, int i)
{
	if(!strcmp(argv[i], "-p") || !strcmp(argv[i], "--path"))
	{
		std::string path = reinterpret_cast<const char*>((argv[i + 1])); // or std::string path{argv[2]};
		if((path.substr(path.length() - 1) != "/") && (path.length() > 0)) // if(argv[2][path.length() - 1] == '/')
			path.append("/");
		workspacePath = path;
		messageUser(MessageType::INFO, "Workspace path: " + workspacePath + "\n");
		return false;
	}
	else if (!strcmp(argv[i], "--loadAll"))
	{
		loadAllImages();
		return false;
	}
	else if (!strcmp(argv[i], "--image"))
	{
		if (!((i + 1) < argc))
		{
			messageUser(MessageType::ERROR, "Missing image parameter\n");
			return false;
		}
		addImage(loadImage(workspacePath + argv[i + 1]));
		if (images.size() > 0)
			convertImage(images.back().get());
		return false;
	}
	else if (!strcmp(argv[i], "--about"))
	{
		GeneralTools::aboutApplication();
		return false;
	}
	return true;
}

void Controller::loadAllImages()
{
	std::string fne = "";
	std::string itDir = workspacePath;
	if (itDir == "")
		itDir = std::filesystem::current_path().generic_string(); // .generic_string(); is required by Windows
	try
	{
		for (const auto& entry : std::filesystem::directory_iterator(itDir))
		{
			fne = entry.path().extension().generic_string();
			if(fne == ".pcx")
				addImage(new Images::ImagePCX(entry.path().generic_string()));
			else if (fne == ".bmp")
				addImage(new Images::ImageBMP(entry.path().generic_string()));
			else if (fne == ".ppm")
				addImage(new Images::ImagePPM(entry.path().generic_string()));
			else
				messageUser(MessageType::WARNING, "Unsupported format \"" + fne + "\"\n");
		}
	}
	catch (std::runtime_error& e)
	{
		messageUser(MessageType::EXCEPTION, e.what());
		return;
	}
	std::sort(images.begin(), images.end(), [](const std::unique_ptr<Images::Image>& a, const std::unique_ptr<Images::Image>& b)
	{
		return a->getFilename() < b->getFilename();
	});
}

bool Controller::addImage(Images::Image* image)
{
	if (image == nullptr)
		return false;
	if (!image->isLoaded())
	{
		messageUser(MessageType::ERROR, image->getFileStatus() + "\n");
		delete image;
		image = NULL;
		return false;
	}
	if(!images.empty())
	{
		for (auto& existingImage : images)
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
		messageUser(MessageType::EXCEPTION, e.what());
		std::cout << "\n";
		return nullptr;
	}
	if (ext == ".pcx")
		return new Images::ImagePCX(path);
	else if (ext == ".bmp")
		return new Images::ImageBMP(path);
	else if (ext == ".ppm")
		return new Images::ImagePPM(path);
	else
		messageUser(MessageType::WARNING, ext + " is not supported\n");
	return nullptr;
}

Controller::~Controller()
{
	//for(size_t i = 0; i < images.size(); i++)
	//	delete images[i];
	//std::cout << "Controller " << "destructed" << std::endl;
}
}
