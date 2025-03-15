//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Mar 4, 2025
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
#include <functional>
#include <thread>

#include "../../images/Formats.hpp"
#include "../imageTools/AsciiConverter.h"
#include "../interfaces/IMenu.hpp"
#include "../tools/GeneralTools.hpp"
#include "../abstract/AbstractNotifier.h"
#include "../interfaces/IMenu.hpp"
#include "../abstract/AbstractAsciiPrinter.h"
#include "../../other/OtherUtils.hpp"
#include "../../math/MathUtils.hpp"

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
	std::unordered_map<std::string, Images::ImageType> supportedImageFormats;
	std::mutex mutexImageFormats;
	std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
	[[deprecated("CLI only")]]
	void convertImage(Images::Image* image);
	// For main state
	virtual Images::Image* selectImage() = 0;
	virtual void showAboutApplicationInfo() = 0;
public:
	Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	virtual ~Controller();
	void configure(std::map<std::string, std::vector<std::string>>& config);
	virtual void run() = 0;
	// Controller
	virtual std::string inputImageName() = 0;
	bool addImageAsync(Images::Image* image);
	Images::Image* loadImageAsync(const std::string& path);
	Images::Image* loadImageAsync(const std::string& path, const std::string& extension);
	void loadAllImagesAsync();
	void convertImage(Images::Image* image, ImageUtils::AsciiConverter::CHAR_SETS charSet);
	void iterateImagesAsync(std::function<void(Images::Image*)> actionOnImage);
	// Setters
	void setWorkspace(std::string path);
	void setSelectedImage(Images::Image* selectedImage);
	// Getters
	AbstractNotifier& getMessenger();
	const std::string& getWorkspace();
	Images::Image* getSelectedImage();
};
}
#endif
