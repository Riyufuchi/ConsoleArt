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
	loadImage();
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

	pixelData.resize(width * height * channels); // This also zero fills
}

ImagePNG::~ImagePNG()
{
}

Images::Pixel ImagePNG::getPixel(int x, int y) const
{
	x = technical.channels * (y * image.width + x);
	if (technical.channels == 4)
		return {pixelData[x], pixelData[x + 1], pixelData[x + 2], pixelData[x + 3]};
	else
		return {pixelData[x], pixelData[x + 1], pixelData[x + 2]};
}
void ImagePNG::setPixel(int x, int y, Images::Pixel newPixel)
{
	x = technical.channels * (y * image.width + x);
	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	pixelData[x + 2] = newPixel.blue;
	if (technical.channels == 4)
		pixelData[x + 3] = newPixel.alpha;
}
bool ImagePNG::saveImage() const
{
	return stbi_write_png(filepath.c_str(), image.width, image.height, technical.channels, pixelData.data(), image.width * technical.channels);
}
void ImagePNG::loadImage()
{
	unsigned char* imageData = stbi_load(filepath.c_str(), &image.width, &image.height, &technical.channels, 0);
	if (imageData == nullptr)
	{
		technical.fileState = ERROR;
		technical.technicalMessage = "Loading of " + filepath + " failed";
		return;
	}
	image.bits = technical.channels * 8;
	pixelData.resize(image.width * image.height * technical.channels); // Resize the class vector to hold image data
	std::memcpy(pixelData.data(), imageData, pixelData.size()); // Copy the raw bytes
	stbi_image_free(imageData); // Always free the original STB data
	technical.fileState = OK;
}
} /* namespace Images */
