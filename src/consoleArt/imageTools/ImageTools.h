//==============================================================================
// File       : ImageTools.h
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGEUTILS_IMAGETOOLS_H_
#define IMAGEUTILS_IMAGETOOLS_H_

#include <iostream>

#include "../../images/Image.h"
#include "../../images/ImagePNG.h"
#include "../../images/ImagePCX.h"

namespace ImageUtils
{
class ImageTools
{
public:
	ImageTools();
	virtual ~ImageTools();
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
};

} /* namespace ImageUtils */
#endif /* IMAGEUTILS_IMAGETOOLS_H_ */
