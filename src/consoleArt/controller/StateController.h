//==============================================================================
// File       : StateController.h
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLER_STATECONTROLLER_H_
#define CONSOLEART_CONTROLLER_STATECONTROLLER_H_

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <mutex>
#include <unordered_map>

#include "../../images/Formats.hpp"
#include "../tools/GeneralTools.hpp"

namespace ConsoleArt
{
class StateController
{
private:
	std::string workspacePath;
	std::vector<std::unique_ptr<Images::Image>> images;
	std::mutex mutexImages;
	std::unordered_map<std::string, Images::ImageType> suppertedImageFormats;
	std::mutex mutexImageFormats;
public:
	StateController(std::string path);
	virtual ~StateController();
	bool addImageAsync(Images::Image* image);
	Images::Image* loadImage(std::string path);
	Images::Image* loadImageAsync(const std::string& path);
	Images::Image* loadImageAsync(const std::string path, const std::string& extension);
	void loadAllImagesAsync();
	void convertImage(Images::Image* image);
	// Setters
	void setWorkspace(std::string path);
	// Getters
	const std::string& getWorkspace();
	const std::vector<std::unique_ptr<Images::Image>>& getImages();

};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_CONTROLLER_STATECONTROLLER_H_ */
