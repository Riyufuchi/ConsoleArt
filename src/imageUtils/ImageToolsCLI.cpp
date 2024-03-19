//==============================================================================
// File       : ImageTools.cpp
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Mar 19, 2024
// Copyright  : Copyright (c) Riyufuchi
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
	if (image == nullptr || !image->isLoaded())
		return;
	Images::Image::ImageInfo info = image->getImageInfo();
	std::cout << "Name: " << info.name << "\n";
	std::cout << "Width: " << info.width << " px\n";
	std::cout << "Height: " << info.height << " px\n";
	std::cout << "Type: " << info.bits << " bit\n";
	std::cout << "Inverted: " << (image->isInverted() ? "Yes" : "No") << "\n";
}
} /* namespace ImageUtils */
