//============================================================================
// Name        : AsciiConverter.cpp
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 15.11.2022
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
//#include "../ImageBMP.h"
#include "../consoleUtils/ConsoleUtility.h"
#include "../consoleUtils//UnixConsole.h"
#include "../imgUtils/AsciiConverter.h"

class Controller
{
private:
	std::vector<std::string> paths;
	ImageBMP loadImage(std::string path);
	int createMenu();
	void linuxVersion(ImageBMP img);
public:
	Controller(std::string path);
	void run();
	~Controller();
};
#endif
