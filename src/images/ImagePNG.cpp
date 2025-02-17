//==============================================================================
// File       : ImagePNG.cpp
// Author     : riyufuchi
// Created on : Feb 17, 2025
// Last edit  : Feb 17, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "ImagePNG.h"

namespace Images {

ImagePNG::ImagePNG(std::string filepath) : Image(filepath)
{
	fileState = OK;
	imageInfo.name = filename;
	this->imageData = stbi_load(filepath.c_str(), &imageInfo.width, &imageInfo.height, &CHANNELS, 0);
	if (imageData == nullptr)
	{
		fileState = ERROR;
		fileStatus = "Image loading failed.";
	}
}

ImagePNG::~ImagePNG()
{
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
	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	pixelData[x + 2] = newPixel.blue;
	if (CHANNELS == 4)
		pixelData[x + 3] = newPixel.alpha;
}
bool ImagePNG::saveImage() const
{
	return false;
}
void ImagePNG::loadImage()
{
}
} /* namespace Images */
