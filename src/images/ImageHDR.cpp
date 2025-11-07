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

ImageHDR::ImageHDR(std::string filename) : Image(filename)
{
	loadImage();
}

ImageHDR::~ImageHDR()
{
}

Images::Pixel ImageHDR::getPixel(int x, int y) const
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return {};

	const int idx = (y * image.width + x) * technical.channels;

	Pixel p;
	p.red = pixelData[idx];
	p.green = pixelData[idx + 1];
	p.blue = (technical.channels > 2) ? pixelData[idx + 2] : 0;
	p.alpha = (technical.channels > 3) ? pixelData[idx + 3] : 255;
	return p;
}

void ImageHDR::setPixel(int x, int y, Images::Pixel newPixel)
{
	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return;

	const int idx = (y * image.width + x) * technical.channels;

	pixelData[idx] = newPixel.red;
	pixelData[idx + 1] = newPixel.green;
	if (technical.channels > 2)
		pixelData[idx + 2] = newPixel.blue;
	if (technical.channels > 3)
		pixelData[idx + 3] = newPixel.alpha;
}

bool ImageHDR::saveImage() const
{
	std::vector<float> hdr;
	hdr.reserve(image.width * image.height * technical.channels);

	for (uint8_t v : pixelData)
		hdr.push_back(v / 255.0f);

	return stbi_write_hdr(filepath.c_str(), image.width, image.height, technical.channels, hdr.data()) != 0;
}

/*
 * This implementation do not support HDR fully, but it will do for now
 **/
void ImageHDR::loadImage()
{
	unsigned char* imageData = stbi_load(filepath.c_str(), &image.width, &image.height, &technical.channels, 0);
	if (!imageData)
	{
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

} /* namespace Images */
