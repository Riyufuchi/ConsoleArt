//==============================================================================
// File       : ImageTools.h
// Author     : riyufuchi
// Created on : Dec 01, 2023
// Last edit  : Dec 19, 2025
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef IMAGEUTILS_IMAGETOOLS_H_
#define IMAGEUTILS_IMAGETOOLS_H_

#include <iostream>

#include "../image_formats.hpp"

namespace consoleartlib::image_tools
{
[[deprecated("Equal to image >> addStr")]]
void addToImageName(consoleartlib::Image& image, const std::string addStr);
int compareImages(const consoleartlib::Image& image1, const consoleartlib::Image& image2);
bool signatureToImage(consoleartlib::Image& canvasImage, const consoleartlib::Image&signature);
void nearestNeighbor(const consoleartlib::Image& originalImage, consoleartlib::Image& scaledImage);
unsigned char* normalizeToRGBA(const consoleartlib::Image& image, consoleartlib::ImageInfo& info);
inline unsigned char* convertPlanarToInterleaved(const unsigned char* planarData, int width, int height)
{
	int totalPixels = width * height;
	unsigned char* interleavedData = new unsigned char[totalPixels * 3]; // Assuming 3 channels (RGB)

	for (int i = 0; i < totalPixels; i++)
	{
		interleavedData[i * 3]     = planarData[i];             // Red plane
		interleavedData[i * 3 + 1] = planarData[i + totalPixels]; // Green plane
		interleavedData[i * 3 + 2] = planarData[i + 2 * totalPixels]; // Blue plane
	}

	return interleavedData;
}
std::unique_ptr<unsigned char[]> convertPlanarPCXToInterleaved(const consoleartlib::ImagePCX& image);
std::unique_ptr<unsigned char[]> convertPlanarPCXToInterleaved(const consoleartlib::ImagePCX::PagePCX& image);
bool convertImage(const consoleartlib::Image& source, consoleartlib::Image& target);
}
#endif
