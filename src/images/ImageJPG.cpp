//==============================================================================
// File       : ImageJPG.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : May 13, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../include/stb_image.h"
#include "../include/stb_image_write.h"
#include "ImageJPG.h"

namespace Images
{
ImageJPG::ImageJPG(std::string filepath) : Image(filepath)
{
	loadImage();
}

ImageJPG::ImageJPG(std::string filepath, int width, int height, int channels) : Image(filepath)
{
	image.width = width;
	image.height = height;
	technical.channels = channels;
	image.bits = technical.channels * 8;
	pixelData.resize(width * height * channels);
	technical.fileState = OK;
}

ImageJPG::~ImageJPG()
{
}

Images::Pixel ImageJPG::getPixel(int x, int y) const
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return {0, 0, 0, 255};
	x = (y * image.width + x) * technical.channels;
	return {pixelData[x], pixelData[x + 1], pixelData[x + 2], (technical.channels == 4 ? pixelData[x + 3] : (uint8_t)255)};
}

void ImageJPG::setPixel(int x, int y, Images::Pixel newPixel)
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;
	x = (y * image.width + x) * technical.channels;
	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	pixelData[x + 2] = newPixel.blue;
	if (technical.channels == 4)
		pixelData[x + 3] = newPixel.alpha;
}

bool ImageJPG::saveImage() const
{
	return stbi_write_jpg(filepath.c_str(), image.width, image.height, technical.channels, pixelData.data(), 100) != 0;
}

void ImageJPG::loadImage()
{
	unsigned char* imageData = stbi_load(filepath.c_str(), &image.width, &image.height, &technical.channels, 0);
	if (!imageData)
	{
		technical.fileState = ERROR;
		technical.technicalMessage = "Image loading failed.";
	}
	else
	{
		image.bits = technical.channels * 8;
		pixelData.resize(image.width * image.height * technical.channels); // Resize the class vector to hold image data
		std::memcpy(pixelData.data(), imageData, pixelData.size()); // Copy the raw bytes
		stbi_image_free(imageData); // Always free the original STB data
		technical.fileState = OK;
	}
}
}

