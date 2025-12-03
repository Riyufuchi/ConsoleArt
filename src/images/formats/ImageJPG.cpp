//==============================================================================
// File       : ImageJPG.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Nov 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../utils/stb_image.h"
#include "../utils/stb_image_write.h"
#include "ImageJPG.h"

namespace consoleartlib
{
ImageJPG::ImageJPG(std::string filepath) : Image(filepath, ImageType::JPG)
{
	loadImage();
}

ImageJPG::ImageJPG(std::string filepath, int width, int height, int channels) : Image(filepath, ImageType::JPG)
{
	image.width = width;
	image.height = height;
	image.channels = channels;
	image.bits = image.channels * 8;
	pixelData.resize(width * height * channels);
	technical.fileState =  FileState::OK;
}

ImageJPG::~ImageJPG()
{
}

consoleartlib::Pixel ImageJPG::getPixel(int x, int y) const
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return {0, 0, 0, 255};
	x = (y * image.width + x) * image.channels;
	return {pixelData[x], pixelData[x + 1], pixelData[x + 2], (image.channels == 4 ? pixelData[x + 3] : (uint8_t)255)};
}

void ImageJPG::setPixel(int x, int y, consoleartlib::Pixel newPixel)
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;
	x = (y * image.width + x) * image.channels;
	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	pixelData[x + 2] = newPixel.blue;
	if (image.channels == 4)
		pixelData[x + 3] = newPixel.alpha;
}

bool ImageJPG::saveImage() const
{
	return stbi_write_jpg(filepath.c_str(), image.width, image.height, image.channels, pixelData.data(), 100) != 0;
}

void ImageJPG::loadImage()
{
	unsigned char* imageData = stbi_load(filepath.c_str(), &image.width, &image.height, &image.channels, 0);
	if (!imageData)
	{
		technical.technicalMessage = "Image loading failed.";
	}
	else
	{
		image.bits = image.channels * 8;
		pixelData.resize(image.width * image.height * image.channels); // Resize the class vector to hold image data
		std::memcpy(pixelData.data(), imageData, pixelData.size()); // Copy the raw bytes
		stbi_image_free(imageData); // Always free the original STB data
		technical.fileState =  FileState::OK;
	}
}
}

