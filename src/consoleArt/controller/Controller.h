//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Jan 20, 2025
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
	// Virtual
	virtual void refreshMenu() = 0;
	virtual void convertImage(Images::Image* image) = 0;
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	// Methods
	void loadAllImagesAsync();
	// Functions
	Images::Image* loadImage(std::string path);
public:
	Controller();
	Controller(std::string path);
	virtual ~Controller();
	virtual void configure(std::map<std::string, std::vector<std::string>>& config) = 0;
	virtual void run() = 0;
	bool addImage(Images::Image* image);
	// Setters
	void setWorkspace(std::string path);
	Messenger& getMessenger()
	{
		return *messenger;
	}
};
}
#endif
