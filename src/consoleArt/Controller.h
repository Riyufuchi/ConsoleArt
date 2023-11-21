//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 21.11.2023
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>

#include "../consoleArt/MenuUtils.hpp"
#include "../images/ImageBMP.h"
#include "../imageUtils/AsciiConverter.h"
#include "../inc/ConsoleUtility.h"
#include "../inc/UnixConsole.h"
#include "../inc/Colors.h"

namespace ConsoleArt
{
//TODO: Make this into abstract or base class for LinuxController and WindowsController
//TODO: Replace ImageBMP with Image reference
class Controller
{
private:
	std::string workspacePath;
	std::vector<Images::Image*> images;
	ConsoleUtils::UnixConsole unxConsole;
	void linuxVersion(Images::ImageBMP image);
	void confConsoleColor();
	Images::ImageBMP selectImage();
	Images::ImageBMP loadImage(std::string path);
public:
	Controller();
	Controller(std::string path);
	void configure(int argc, char** argv);
	void run();
	~Controller();
};
}
#endif
