//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Apr 28, 2024
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <mutex>

#include "../../images/ImageBMP.h"
#include "../../images/ImagePCX.h"
#include "../../images/ImagePPM.h"
#include "../../imageUtils/AsciiConverter.h"
#include "../interfaces/IMenu.hpp"
#include "../tools/GeneralTools.hpp"
#include "../messenger/Messenger.h"


namespace ConsoleArt
{
class Controller
{
protected:
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	std::mutex mutexImages;
	bool isRunnable;
	Messenger* messenger;
	// Methods
	virtual void convertImage(Images::Image* image) = 0;
	void loadAllImagesAsync();
	// Functions
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	Images::Image* loadImage(std::string path);
	bool applyArgument(int arg, char** argv, int i);
	virtual void refreshMenu() = 0;
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
