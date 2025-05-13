//==============================================================================
// File       : ImagePNG.cpp
// Author     : riyufuchi
// Created on : Feb 17, 2025
// Last edit  : May 13, 2025
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
	technical.fileState = OK;
	this->imageData = stbi_load(filepath.c_str(), &image.width, &image.height, &technical.channels, 0);
	image.bits = technical.channels * 8;
	if (imageData == nullptr)
	{
		technical.fileState = ERROR;
		technical.technicalMessage = "Loading of " + filepath + " failed";
	}
}
ImagePNG::ImagePNG(std::string filepath, int width, int height, int channels) : Image(filepath)
{
	technical.fileState = OK;
	image.name = filepath;
	image.width = width;
	image.height = height;
	technical.channels = channels;

	switch (channels)
	{
		case 4: image.bits = 32; break;
		case 3: image.bits = 24; break;
		default:
			image.bits = channels * 8; // fallback, e.g., grayscale
			technical.fileState = ERROR;
			technical.technicalMessage = "Only 24 and 32 bit images are supported-";
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
	{
		stbi_image_free(imageData);
		imageData = nullptr;
	}
}

Images::Pixel ImagePNG::getPixel(int x, int y) const
{
	x = technical.channels * (y * image.width + x);
	if (technical.channels == 4)
		return {imageData[x], imageData[x + 1], imageData[x + 2], imageData[x + 3]};
	else
		return {imageData[x], imageData[x + 1], imageData[x + 2]};
}
void ImagePNG::setPixel(int x, int y, Images::Pixel newPixel)
{
	x = technical.channels * (y * image.width + x);
	imageData[x] = newPixel.red;
	imageData[x + 1] = newPixel.green;
	imageData[x + 2] = newPixel.blue;
	if (technical.channels == 4)
		imageData[x + 3] = newPixel.alpha;
}
bool ImagePNG::saveImage() const
{
	return stbi_write_png(filepath.c_str(), image.width, image.height, technical.channels, imageData, image.width * technical.channels);
}
void ImagePNG::loadImage()
{
}
} /* namespace Images */
