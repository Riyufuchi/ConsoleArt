//==============================================================================
// File       : ImageJPG.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Feb 28, 2025
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
	imageData = stbi_load(filepath.c_str(), &imageInfo.width, &imageInfo.height, &CHANNELS, 0);
	loadImage();
}

ImageJPG::ImageJPG(std::string filepath, int width, int height, int channels) : Image(filepath)
{
	imageInfo.width = width;
	imageInfo.height = height;
	CHANNELS = channels;
	imageInfo.bits = CHANNELS * 8;
	imageData = new unsigned char[width * height * CHANNELS](); // Allocate blank image
}

ImageJPG::~ImageJPG()
{
	if (imageData)
	{
		stbi_image_free(imageData);
	}
}

Images::Pixel ImageJPG::getPixel(int x, int y) const
{
	if (!imageData || x < 0 || y < 0 || x >= imageInfo.width || y >= imageInfo.height)
		return {0, 0, 0, 255};
	x = (y * imageInfo.width + x) * CHANNELS;
	return {imageData[x], imageData[x + 1], imageData[x + 2], (CHANNELS == 4 ? imageData[x + 3] : (uint8_t)255)};
}

void ImageJPG::setPixel(int x, int y, Images::Pixel newPixel)
{
	if (!imageData || x < 0 || y < 0 || x >= imageInfo.width || y >= imageInfo.height)
		return;
	x = (y * imageInfo.width + x) * CHANNELS;
	imageData[x] = newPixel.red;
	imageData[x + 1] = newPixel.green;
	imageData[x + 2] = newPixel.blue;
	if (CHANNELS == 4)
		imageData[x + 3] = newPixel.alpha;
}

bool ImageJPG::saveImage() const
{
	if (!imageData)
		return false;
	return stbi_write_jpg(filepath.c_str(), imageInfo.width, imageInfo.height, CHANNELS, imageData, 100) != 0;
}

void ImageJPG::loadImage()
{
	if (imageData)
	{
		stbi_image_free(imageData);
	}
	imageData = stbi_load(filepath.c_str(), &imageInfo.width, &imageInfo.height, &CHANNELS, 0);
	if (!imageData)
	{
		fileState = ERROR;
		fileStatus = "Image loading failed.";
	}
	else
	{
		fileState = OK;
		imageInfo.bits = CHANNELS * 8;
	}
}
}

