//==============================================================================
// File       : ImageTools.cpp
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Dec 1, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageToolsCLI.h"

namespace ImageUtils
{
ImageToolsCLI::ImageToolsCLI()
{
}
ImageToolsCLI::~ImageToolsCLI()
{
}
void ImageToolsCLI::displayImageInfo(Images::Image* image)
{
	if (image == nullptr)
		return;
	Images::Image::ImageInfo info = image->getImageInfo();
	std::cout << "Name: " << info.name << "\n";
	std::cout << "Width: " << info.width << "\n";
	std::cout << "Height: " << info.height << "\n";
	std::cout << "Types: " << info.bits << " bit" << "\n";
}
} /* namespace ImageUtils */
