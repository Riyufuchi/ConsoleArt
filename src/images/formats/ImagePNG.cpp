//==============================================================================
// File       : ImagePNG.cpp
// Author     : riyufuchi
// Created on : Feb 17, 2025
// Last edit  : Dec 03, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

//#define STB_IMAGE_IMPLEMENTATION
//#include "../utils/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../utils/stb_image_write.h"
#include "ImagePNG.h"

namespace consoleartlib
{
ImagePNG::ImagePNG(std::string filepath) : Image(filepath, ImageType::PNG)
{
	loadImage();
}
ImagePNG::ImagePNG(std::string filepath, int width, int height, int channels) : Image(filepath, ImageType::PNG)
{
	technical.fileState =  FileState::OK;
	image.name = filepath;
	image.width = width;
	image.height = height;
	image.channels = channels;

	switch (channels)
	{
		case 4: image.bits = 32; break;
		case 3: image.bits = 24; break;
		default:
			image.bits = channels * 8; // fallback, e.g., grayscale
			technical.technicalMessage = "Only 24 and 32 bit images are supported-";
		break;
	}

	pixelData.resize(width * height * channels); // This also zero fills
}

ImagePNG::~ImagePNG()
{
}

consoleartlib::Pixel ImagePNG::getPixel(int x, int y) const
{
	x = image.channels * (y * image.width + x);
	if (image.channels == 4)
		return {pixelData[x], pixelData[x + 1], pixelData[x + 2], pixelData[x + 3]};
	else
		return {pixelData[x], pixelData[x + 1], pixelData[x + 2]};
}
void ImagePNG::setPixel(int x, int y, consoleartlib::Pixel newPixel)
{
	x = image.channels * (y * image.width + x);
	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	pixelData[x + 2] = newPixel.blue;
	if (image.channels == 4)
		pixelData[x + 3] = newPixel.alpha;
}
bool ImagePNG::saveImage() const
{
	return stbi_write_png(filepath.c_str(), image.width, image.height, image.channels, pixelData.data(), image.width * image.channels);
}
void ImagePNG::loadImage()
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
