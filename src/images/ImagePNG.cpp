//==============================================================================
// File       : ImagePNG.cpp
// Author     : riyufuchi
// Created on : Feb 17, 2025
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "ImagePNG.h"

namespace Images
{
ImagePNG::ImagePNG(std::string filepath) : Image(filepath)
{
	fileState = OK;
	imageInfo.name = filename;
	this->imageData = stbi_load(filepath.c_str(), &imageInfo.width, &imageInfo.height, &CHANNELS, 0);
	if (CHANNELS == 4)
	{
		imageInfo.bits = 32;
	}
	if (imageData == nullptr)
	{
		fileState = ERROR;
		fileStatus = "Loading of " + filepath + " failed";
	}
}
ImagePNG::ImagePNG(std::string filepath, int width, int height, int channels) : Image(filepath)
{
	fileState = OK;
	imageInfo.name = filepath;
	imageInfo.width = width;
	imageInfo.height = height;
	CHANNELS = channels;

	switch (channels)
	{
		case 4: imageInfo.bits = 32; break;
		case 3: imageInfo.bits = 24; break;
		default:
			imageInfo.bits = channels * 8; // fallback, e.g., grayscale
			fileState = ERROR;
			fileStatus = "Only 24 and 32 bit images are supported-";
		break;
	}

	// Allocate memory for the blank image
	imageData = new unsigned char[width * height * channels];

	// Initialize the image to a default color, e.g., black
	memset(imageData, 0, width * height * channels);
}

ImagePNG::~ImagePNG()
{
	if (imageData)
		stbi_image_free(imageData);
}

Images::Pixel ImagePNG::getPixel(int x, int y) const
{
	x = CHANNELS * (y * imageInfo.width + x);
	if (CHANNELS == 4)
		return {imageData[x], imageData[x + 1], imageData[x + 2], imageData[x + 3]};
	else
		return {imageData[x], imageData[x + 1], imageData[x + 2]};
}
void ImagePNG::setPixel(int x, int y, Images::Pixel newPixel)
{
	x = CHANNELS * (y * imageInfo.width + x);
	imageData[x] = newPixel.red;
	imageData[x + 1] = newPixel.green;
	imageData[x + 2] = newPixel.blue;
	if (CHANNELS == 4)
		imageData[x + 3] = newPixel.alpha;
}
bool ImagePNG::saveImage() const
{
	return stbi_write_png(filepath.c_str(), imageInfo.width, imageInfo.height, CHANNELS, imageData, imageInfo.width * CHANNELS);
}
void ImagePNG::loadImage()
{
}
} /* namespace Images */
