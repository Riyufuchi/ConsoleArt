//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : 15.11.2022
// Last Edit   : Mar 4, 2024
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

#include "../ConsoleArtTools.hpp"
#include "../../images/ImageBMP.h"
#include "../../images/ImagePCX.h"
#include "../../imageUtils/AsciiConverter.h"
#include "../interfaces/IMenu.hpp"

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
private:
	//IMenu& menu; // TODO: Implement methods from Controller
protected:
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	virtual void convertImage(Images::Image* image) = 0;
	void loadAllImages();
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	Images::Image* loadImage(std::string path);
	bool applyArgument(int arg, char** argv, int i);
	virtual void messageUser(MessageType messageSeverity, std::string message) = 0;
public:
	Controller();
	Controller(std::string path);
	virtual void configure(int argc, char** argv) = 0;
	virtual void run() = 0;
	bool addImage(Images::Image* image);
	virtual ~Controller();
};
}
#endif
