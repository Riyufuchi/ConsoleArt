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
	imageData = new unsigned char[width * height * technical.channels](); // Allocate blank image
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
	if (!imageData || x < 0 || y < 0 || x >= image.width || y >= image.height)
		return {0, 0, 0, 255};
	x = (y * image.width + x) * technical.channels;
	return {imageData[x], imageData[x + 1], imageData[x + 2], (technical.channels == 4 ? imageData[x + 3] : (uint8_t)255)};
}

void ImageJPG::setPixel(int x, int y, Images::Pixel newPixel)
{
	if (!imageData || x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;
	x = (y * image.width + x) * technical.channels;
	imageData[x] = newPixel.red;
	imageData[x + 1] = newPixel.green;
	imageData[x + 2] = newPixel.blue;
	if (technical.channels == 4)
		imageData[x + 3] = newPixel.alpha;
}

bool ImageJPG::saveImage() const
{
	if (!imageData)
		return false;
	return stbi_write_jpg(filepath.c_str(), image.width, image.height, technical.channels, imageData, 100) != 0;
}

void ImageJPG::loadImage()
{
	if (imageData)
	{
		stbi_image_free(imageData);
	}
	imageData = stbi_load(filepath.c_str(), &image.width, &image.height, &technical.channels, 0);
	if (!imageData)
	{
		technical.fileState = ERROR;
		technical.technicalMessage = "Image loading failed.";
	}
	else
	{
		technical.fileState = OK;
		image.bits = technical.channels * 8;
	}
}
}

