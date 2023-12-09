//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 07.12.2023
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>

#include "../consoleArt/MenuUtils.hpp"
#include "../images/ImageBMP.h"
#include "../images/ImagePCX.h"
#include "../imageUtils/AsciiConverter.h"
#include "../inc/ConsoleUtility.h"
#include "../inc/UnixConsole.h"
#include "../inc/Colors.h"
#include <memory>
#include <algorithm>
#include "ConsoleArtTools.hpp"

namespace ConsoleArt
{
class Controller
{
private:
protected:
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	ConsoleUtils::IConsole& console;
	virtual void convertImage(Images::Image* image) = 0;
	virtual void confConsoleColor() = 0;
	virtual void loadAllImages() = 0;
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	virtual Images::Image* loadImage(std::string path) = 0;
public:
	Controller(ConsoleUtils::IConsole& console);
	Controller(std::string path, ConsoleUtils::IConsole& console);
	void configure(int argc, char** argv);
	virtual void run() = 0;
	bool addImage(Images::Image* image);
	ConsoleUtils::IConsole& getConslole()
	{
		return console;
	}
	virtual ~Controller();
};
}
#endif
