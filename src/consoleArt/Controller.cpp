//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 01.12.2023
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

namespace ConsoleArt
{
Controller::Controller(ConsoleUtils::IConsole& console) : Controller("", console) //Calls constructor with parameter to construct class
{
}
Controller::Controller(std::string path, ConsoleUtils::IConsole& console) : workspacePath(path), console(console)
{
}

void Controller::configure(int argc, char** argv)
{
	for(int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-p") || !strcmp(argv[i], "--path"))
		{
			std::string path = reinterpret_cast<const char*>((argv[i + 1])); //or std::string path{argv[2]};
			if((path.substr(path.length() - 1) != "/") && (path.length() > 0)) //if(argv[2][path.length() - 1] == '/')
				path.append("/");
			workspacePath = path;
			std::cout << "Workspace path: " << workspacePath << std::endl;
		}
		else if (!strcmp(argv[i], "--loadAll"))
		{
			loadAllImages();
		}
		else if (!strcmp(argv[i], "--image"))
		{
			if (!((i + 1) < argc))
			{
				console.out(255, 0, 0, "Missing image name parameter\n");
				continue;
			}
			addImage(std::unique_ptr<Images::Image>(loadImage(workspacePath + argv[i + 1])));
			if (images.size() > 0)
				convertImage(images.back().get());
		}
		else if (!strcmp(argv[i], "--imagePath"))
		{
			if (!((i + 1) < argc))
			{
				console.out(255, 0, 0, "Missing path parameter\n");
				continue;
			}
			addImage(std::unique_ptr<Images::Image>(loadImage(argv[i + 1])));
			if (images.size() > 0)
				convertImage(images.back().get());
		}
		else if (argv[i][0] == '-') // Check if is it argument or arg param
		{
			ConsoleArtTools::printArgError(argv[i], console);
		}
	}
}

void Controller::addImage(std::unique_ptr<Images::Image> image)
{
	if (image.get() == nullptr)
		return;
	if (!image.get()->isLoaded())
	{
		console.out(255, 0, 0, image->getFileStatus() + "\n");
		return;
	}
	if(!images.empty())
	{
		int maxIndex = images.size();
		for(int i = 0; i < maxIndex; i++)
			if(images[i]->getFilename() == image->getFilename())
				return;
	}
	images.push_back(std::move(image));
}

Controller::~Controller()
{
	//for(size_t i = 0; i < images.size(); i++)
		//delete images[i];
	std::cout << "Controller " << "destructed" << std::endl;
}
}
