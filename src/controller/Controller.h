//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 13.10.2023
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include "../imgUtils/ImageBMP.h"
#include "../inc/ConsoleUtility.h"
#include "../inc/UnixConsole.h"
#include "../imgUtils/AsciiConverter.h"
#include "MenuUtils.hpp"

using namespace ConsoleUtils;

//TODO: Make this into abstract or base class for LinuxController and WindowsController
class Controller
{
private:
	std::string workspacePath;
	std::vector<ImageBMP> bmpImages;
	UnixConsole unxConsole;
	void linuxVersion(ImageBMP image);
	void confConsoleColor();
	ImageBMP selectImage();
	ImageBMP loadImage(std::string path);
public:
	Controller();
	Controller(std::string path);
	void configure(int argc, char** argv);
	void run();
	~Controller();
};
#endif
