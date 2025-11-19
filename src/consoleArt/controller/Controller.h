//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Nov 19, 2025
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
#include <memory>

// ConsoleLib
#include "ArgumentParser.h"
//Image utils
#include "../imageTools/AsciiConverter.h"
#include "../imageTools/SimpleEdit.h"
//
#include "../../images/formats/Formats.hpp"
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
public:
	using IndexDataType = uint32_t;

	struct VectorNode
	{
		IndexDataType index;
		std::unique_ptr<Images::Image> imageUptr;
	};

	using VectorData = VectorNode;
private:
	IndexDataType selectedImageIndex;
protected:
	bool isRunnable;
	AbstractNotifier* messenger;
	IMenu* menuInterface;
	AbstractAsciiPrinter* abstractAsciiPrinter;
	std::string workspacePath;
	std::vector<VectorData> images;
	std::mutex mutexImages;
	std::unordered_map<std::string, Images::ImageType> supportedImageFormats;
	std::mutex mutexImageFormats;
	std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> argumentMethods;
	// For main state
	virtual IndexDataType selectImageMenu() = 0;
	virtual void showAboutApplicationInfo() = 0;
public:
	Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	virtual ~Controller();
	void configure(ConsoleLib::argMap& config);
	void configure(ConsoleLib::argVector& config);
	virtual void run() = 0;
	// Controller
	virtual std::string inputImageName() = 0;
	IndexDataType addImageAsync(Images::Image* image);
	Images::Image* loadImageAsync(const std::string& path);
	Images::Image* loadImageAsync(const std::string& path, const std::string& extension);
	void loadAllImagesAsync();
	void convertImage(Images::Image* image, ImageUtils::AsciiConverter::CHAR_SETS charSet);
	void iterateImagesAsync(std::function<void(const VectorNode& node)> actionOnImage);
	void notifyUser(AbstractNotifier::MessageType messageType, const std::string& message);
	void displayImageInfo(const Images::Image& image);
	// Setters
	void setWorkspace(std::string path);
	void selectImage(IndexDataType selectedImageIndex);
	void setNotifier(AbstractNotifier* notifier);
	void setMenu(IMenu* imenu);
	// Getters
	IndexDataType getSelectedImageIndex() const;
	int getNumberOfLoadedImages();
	const std::string& getWorkspace();
	Images::Image* getSelectedImage();
};
}
#endif
