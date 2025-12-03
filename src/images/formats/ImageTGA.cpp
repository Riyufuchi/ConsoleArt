//==============================================================================
// File       : ImageTGA.cpp
// Author     : riyufuchi
// Created on : Nov 07, 2025
// Last edit  : Nov 09, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../utils/stb_image.h"
#include "../utils/stb_image_write.h"
#include "ImageTGA.h"

namespace consoleartlib
{

ImageTGA::ImageTGA(std::string filename) : Image(filename, ImageType::TGA)
{
	loadImage();
}

consoleartlib::Pixel ImageTGA::getPixel(int x, int y) const
{
	x = image.channels * (y * image.width + x);
	if (image.channels == 4)
		return {pixelData[x], pixelData[x + 1], pixelData[x + 2], pixelData[x + 3]};
	else
		return {pixelData[x], pixelData[x + 1], pixelData[x + 2]};
}

void ImageTGA::setPixel(int x, int y, consoleartlib::Pixel newPixel)
{
	x = image.channels * (y * image.width + x);
	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	pixelData[x + 2] = newPixel.blue;
	if (image.channels == 4)
		pixelData[x + 3] = newPixel.alpha;
}

bool ImageTGA::saveImage() const
{
	return stbi_write_tga(filepath.c_str(), image.width, image.height, image.channels, pixelData.data());
}

void ImageTGA::loadImage()
{
	unsigned char* imageData = stbi_load(filepath.c_str(), &image.width, &image.height, &image.channels, 0);
	if (imageData == nullptr)
	{
		technical.technicalMessage = "Loading of " + filepath + " failed";
		return;
	}
	image.bits = image.channels * 8;
	pixelData.resize(image.width * image.height * image.channels); // Resize the class vector to hold image data
	std::memcpy(pixelData.data(), imageData, pixelData.size()); // Copy the raw bytes
	stbi_image_free(imageData); // Always free the original STB data
	technical.fileState =  FileState::OK;
}

} /* namespace consoleartlib */
