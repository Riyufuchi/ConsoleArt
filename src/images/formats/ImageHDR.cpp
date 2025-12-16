//==============================================================================
// File       : ImageHDR.cpp
// Author     : riyufuchi
// Created on : Nov 07, 2025
// Last edit  : Dec 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../utils/stb_image.h"
#include "../utils/stb_image_write.h"
#include "ImageHDR.h"

namespace consoleartlib
{

ImageHDR::ImageHDR(const std::string& filename, bool convert) : Image(filename, ImageType::HDR)
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

	x = (y * image.width + x) * image.channels;

	return {
		pixelDataHDR[x],
		pixelDataHDR[x + 1],
		(image.channels > 2) ? pixelDataHDR[x + 2] : 0.0f,
		(image.channels > 3) ? pixelDataHDR[x + 3] : 1.0f
	};
}

void ImageHDR::setPixelHDR(int x, int y, PixelHDR newPixel)
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;

	x = (y * image.width + x) * image.channels;

	pixelDataHDR[x] = newPixel.red;
	pixelDataHDR[x + 1] = newPixel.green;
	if (image.channels > 2)
		pixelDataHDR[x + 2] = newPixel.blue;
	if (image.channels > 3)
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

consoleartlib::Pixel ImageHDR::getPixel(int x, int y) const
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return {};

	x = (y * image.width + x) * image.channels;

	Pixel p;
	p.red = pixelData[x];
	p.green = pixelData[x + 1];
	p.blue = (image.channels > 2) ? pixelData[x + 2] : 0;
	p.alpha = (image.channels > 3) ? pixelData[x + 3] : 255;
	return p;
}

void ImageHDR::setPixel(int x, int y, consoleartlib::Pixel newPixel)
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;

	x = (y * image.width + x) * image.channels;

	pixelData[x] = newPixel.red;
	pixelData[x + 1] = newPixel.green;
	if (image.channels > 2)
		pixelData[x + 2] = newPixel.blue;
	if (image.channels > 3)
		pixelData[x + 3] = newPixel.alpha;
}

bool ImageHDR::saveImage() const
{
	if (pixelDataHDR.empty())
		return false;
	return stbi_write_hdr(filepath.c_str(), image.width, image.height, image.channels, pixelDataHDR.data()) != 0;
}

void ImageHDR::loadImage()
{
	float* imageDataHDR = stbi_loadf(filepath.c_str(), &image.width, &image.height, &image.channels, 0);
	if (!imageDataHDR)
	{
		technical.technicalMessage = "Image loading failed.";
	}
	else
	{
		image.bits = image.channels * 8;
		image.hdr = true;
		pixelDataHDR.resize(image.width * image.height * image.channels); // Resize the class vector to hold image data
		std::memcpy(pixelDataHDR.data(), imageDataHDR, pixelDataHDR.size() * sizeof(float)); // Copy the raw bytes
		stbi_image_free(imageDataHDR); // Always free the original STB data
		technical.fileState = FileState::VALID_IMAGE_FILE;
	}
}

} /* namespace consoleartlib */
