//==============================================================================
// File       : ImageHDR.cpp
// Author     : riyufuchi
// Created on : Nov 7, 2025
// Last edit  : Nov 7, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../include/stb_image.h"
#include "../include/stb_image_write.h"
#include "ImageHDR.h"

namespace Images
{

ImageHDR::ImageHDR(std::string filename, bool convert) : Image(filename)
{
	loadImage();
	if (convert && isLoaded())
		convertTo8bit();
}

ImageHDR::~ImageHDR()
{
}

PixelHDR ImageHDR::getPixelHDR(int x, int y) const
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return {};

	x = (y * image.width + x) * technical.channels;

	return {
		pixelDataHDR[x],
		pixelDataHDR[x + 1],
		(technical.channels > 2) ? pixelDataHDR[x + 2] : 0.0f,
		(technical.channels > 3) ? pixelDataHDR[x + 3] : 1.0f
	};
}

void ImageHDR::setPixelHDR(int x, int y, PixelHDR newPixel)
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;

	x = (y * image.width + x) * technical.channels;

	pixelDataHDR[x] = newPixel.red;
	pixelDataHDR[x + 1] = newPixel.green;
	if (technical.channels > 2)
		pixelDataHDR[x + 2] = newPixel.blue;
	if (technical.channels > 3)
		pixelDataHDR[x + 3] = newPixel.alpha;
}

void ImageHDR::convertTo8bit()
{
	if (pixelDataHDR.empty())
		return;
	pixelData.reserve(pixelDataHDR.size());
	constexpr float gamma = 1.0f / 2.0f; // sRGB gamma correction
	for (float v : pixelDataHDR)
	{
		v = std::clamp(v, 0.0f, 1.0f);
		pixelData.push_back(std::pow(v, gamma) * 255.0f);
	}
}

void ImageHDR::convertFrom8bit()
{
	if (pixelData.empty())
		return;
	pixelDataHDR.reserve(pixelData.size());
	for (uint8_t v : pixelData)
		pixelDataHDR.push_back(v / 255.0f);
}

Images::Pixel ImageHDR::getPixel(int x, int y) const
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return {};

	x = (y * image.width + x) * technical.channels;

	Pixel p;
	p.red = pixelData[x];
	p.green = pixelData[x + 1];
	p.blue = (technical.channels > 2) ? pixelData[x + 2] : 0;
	p.alpha = (technical.channels > 3) ? pixelData[x + 3] : 255;
	return p;
}

void ImageHDR::setPixel(int x, int y, Images::Pixel newPixel)
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;

	x = (y * image.width + x) * technical.channels;

	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	if (technical.channels > 2)
		pixelData[x + 2] = newPixel.blue;
	if (technical.channels > 3)
		pixelData[x + 3] = newPixel.alpha;
}

bool ImageHDR::saveImage() const
{
	if (pixelDataHDR.empty())
		return false;
	return stbi_write_hdr(filepath.c_str(), image.width, image.height, technical.channels, pixelDataHDR.data()) != 0;
}

void ImageHDR::loadImage()
{
	float* imageDataHDR = stbi_loadf(filepath.c_str(), &image.width, &image.height, &technical.channels, 0);
	if (!imageDataHDR)
	{
		technical.technicalMessage = "Image loading failed.";
	}
	else
	{
		image.bits = technical.channels * 8;
		image.hdr = true;
		pixelDataHDR.resize(image.width * image.height * technical.channels); // Resize the class vector to hold image data
		std::memcpy(pixelDataHDR.data(), imageDataHDR, pixelDataHDR.size() * sizeof(float)); // Copy the raw bytes
		stbi_image_free(imageDataHDR); // Always free the original STB data
		technical.fileState = OK;
	}
}

} /* namespace Images */
