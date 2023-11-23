//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 22.11.2023
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

namespace ConsoleArt
{
Controller::Controller() : Controller("") //Calls constructor with parameter to construct class
{
}
Controller::Controller(std::string path) : workspacePath(path)
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
	}
}

void Controller::addImage(std::unique_ptr<Images::Image> image)
{
	if (image == nullptr)
		return;
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
