//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Feb 25, 2025
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

#include "../../images/ImageBMP.h"
#include "../../images/ImagePCX.h"
#include "../../images/ImagePPM.h"
#include "../../images/ImagePNG.h"
#include "../asciiTools/AsciiConverter.h"
#include "../interfaces/IMenu.hpp"
#include "../tools/GeneralTools.hpp"
#include "../abstract/AbstractNotifier.h"
#include "../interfaces/IMenu.hpp"
#include "../abstract/AbstractAsciiPrinter.h"


namespace ConsoleArt
{
enum Format
{
	BMP,
	PCX,
	PPM,
	PNG
};
class Controller
{
protected:
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	std::mutex mutexImages;
	std::unordered_map<std::string, Format> suppertedImageFormats;
	std::mutex mutexImageFormats;
	bool isRunnable;
	AbstractNotifier* messenger;
	IMenu* menuInterface;
	AbstractAsciiPrinter* abstractAsciiPrinter;
	Images::Image* selectedImage;
	// Virtual
	virtual void refreshMenu() = 0;
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	virtual void showAboutApplicationInfo() = 0;
	// Methods
	void loadAllImagesAsync();
	void convertImage(Images::Image* image);
	// Functions
	Images::Image* loadImage(std::string path);
	Images::Image* loadImageAsync(const std::string& path);
	Images::Image* loadImageAsync(const std::string path, const std::string& extension);
public:
	Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	virtual ~Controller();
	virtual void configure(std::map<std::string, std::vector<std::string>>& config) = 0;
	virtual void run() = 0;
	bool addImageAsync(Images::Image* image);
	// Setters
	void setWorkspace(std::string path);
	AbstractNotifier& getMessenger()
	{
		return *messenger;
	}
};
}
#endif
