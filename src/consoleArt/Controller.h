//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : 18.12.2023
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>

#include "../images/ImageBMP.h"
#include "../images/ImagePCX.h"
#include "../imageUtils/AsciiConverter.h"
#include <memory>
#include <algorithm>
#include "ConsoleArtTools.hpp"

namespace ConsoleArt
{
enum MessageSeverity
{
	EXCEPTION,
	ERROR,
	WARNING,
	SUCCESFUL_TASK,
	INFO
};
class Controller
{
private:
protected:
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	virtual void convertImage(Images::Image* image) = 0;
	virtual void confConsoleColor() = 0;
	void loadAllImages();
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	Images::Image* loadImage(std::string path);
	virtual void messageUser(MessageSeverity messageSeverity, std::string message) = 0;
public:
	Controller();
	Controller(std::string path);
	void configure(int argc, char** argv);
	virtual void run() = 0;
	bool addImage(Images::Image* image);
	virtual ~Controller();
};
}
#endif
