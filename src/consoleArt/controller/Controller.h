//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Mar 19, 2024
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

#include "../../images/ImageBMP.h"
#include "../../images/ImagePCX.h"
#include "../../images/ImagePPM.h"
#include "../../imageUtils/AsciiConverter.h"
#include "../interfaces/IMenu.hpp"
#include "../tools/GeneralTools.hpp"

namespace ConsoleArt
{
enum MessageType
{
	EXCEPTION,
	ERROR,
	WARNING,
	SUCCESFUL_TASK,
	INFO,
	NOTIFICATION
};
class Controller
{
protected:
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	bool isRunnable;
	// Methods
	virtual void convertImage(Images::Image* image) = 0;
	virtual void messageUser(MessageType messageSeverity, std::string message) = 0;
	void loadAllImages();
	// Functions
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	Images::Image* loadImage(std::string path);
	bool applyArgument(int arg, char** argv, int i);
public:
	Controller();
	Controller(std::string path);
	virtual ~Controller();
	virtual void configure(int argc, char** argv) = 0;
	virtual void run() = 0;
	bool addImage(Images::Image* image);
};
}
#endif
