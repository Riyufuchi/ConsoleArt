//==============================================================================
// File       : ImageTools.h
// Author     : riyufuchi
// Created on : Dec 01, 2023
// Last edit  : Nov 20, 2025
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGEUTILS_IMAGETOOLS_H_
#define IMAGEUTILS_IMAGETOOLS_H_

#include <iostream>

#include "../../images/formats/Formats.hpp"

namespace ImageUtils
{
class ImageTools
{
public:
	ImageTools();
	virtual ~ImageTools();
	[[deprecated("Equal to image >> addStr")]]
	static void addToImageName(Images::Image& image, const std::string addStr);
	static int compareImages(const Images::Image& image1, const Images::Image& image2);
	static bool signatureToImage(Images::Image& canvasImage, const Images::Image& signature);
	static void nearestNeighbor(const Images::Image& originalImage, Images::Image& scaledImage);
	static unsigned char* normalizeToRGBA(const Images::Image& image, Images::ImageInfo& info);
	static unsigned char* convertPlanarToInterleaved(const unsigned char* planarData, int width, int height)
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
	static std::unique_ptr<unsigned char[]> convertPlanarPCXToInterleaved(const Images::ImagePCX& image);
	static std::unique_ptr<unsigned char[]> convertPlanarPCXToInterleaved(const Images::ImagePCX::PagePCX& image);
	static bool convertImage(const Images::Image& source, Images::Image& target);
};

} /* namespace ImageUtils */
#endif /* IMAGEUTILS_IMAGETOOLS_H_ */
