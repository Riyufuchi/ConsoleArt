//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Feb 27, 2025
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <mutex>
#include <unordered_map>

#include "../../images/Formats.hpp"
#include "../asciiTools/AsciiConverter.h"
#include "../interfaces/IMenu.hpp"
#include "../tools/GeneralTools.hpp"
#include "../abstract/AbstractNotifier.h"
#include "../interfaces/IMenu.hpp"
#include "../abstract/AbstractAsciiPrinter.h"

namespace ConsoleArt
{
class Controller
{
protected:
	bool isRunnable;
	AbstractNotifier* messenger;
	IMenu* menuInterface;
	AbstractAsciiPrinter* abstractAsciiPrinter;
	Images::Image* selectedImage;
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	std::mutex mutexImages;
	std::unordered_map<std::string, Images::ImageType> suppertedImageFormats;
	std::mutex mutexImageFormats;
	void convertImage(Images::Image* image);
	// For main state
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	virtual void showAboutApplicationInfo() = 0;
	// Controller
	bool addImageAsync(Images::Image* image);
	Images::Image* loadImage(std::string path);
	Images::Image* loadImageAsync(const std::string& path);
	Images::Image* loadImageAsync(const std::string path, const std::string& extension);
	void loadAllImagesAsync();
public:
	Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	virtual ~Controller();
	virtual void configure(std::map<std::string, std::vector<std::string>>& config) = 0;
	virtual void run() = 0;
	// Setters
	void setWorkspace(std::string path);
	// Getters
	AbstractNotifier& getMessenger();
	const std::string& getWorkspace();
	const Images::Image* getSelectedImage();
};
}
#endif
