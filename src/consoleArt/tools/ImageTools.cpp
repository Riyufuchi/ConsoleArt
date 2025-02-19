//==============================================================================
// File       : ImageTools.cpp
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageTools.h"

namespace ImageUtils
{
ImageTools::ImageTools()
{
}
ImageTools::~ImageTools()
{
}
int ImageTools::compareImages(const Images::Image& image1, const Images::Image& image2)
{
	if (image1 == image2)
		return 0;
	else if (image1 > image2)
		return 1;
	else if (image1 < image2)
		return -1;
	else
		return -2;
}
void ImageTools::nearestNeighbor(const Images::Image& originalImage, Images::Image& scaledImage)
{
	const Images::ImageInfo& canvasInfo = originalImage.getImageInfo(); // Old values
	const Images::ImageInfo& scaledInfo = scaledImage.getImageInfo(); // New values

	const double scaleX = static_cast<double>(canvasInfo.width) / scaledInfo.width;
	const double scaleY = static_cast<double>(canvasInfo.height) / scaledInfo.height;

	int srcX = 0;
	int srcY = 0;

	for (int y = 0; y < scaledInfo.height; y++)
	{
		for (int x = 0; x < scaledInfo.width; x++)
		{
			// Clamp to prevent out-of-bounds access
			srcX = std::min(static_cast<int>(x * scaleX), canvasInfo.width - 1);
			srcY = std::min(static_cast<int>(y * scaleY), canvasInfo.height - 1);

			scaledImage.setPixel(x, y, originalImage.getPixel(srcX, srcY));
		}
	}
}

bool ImageTools::signatureToImage(Images::Image& canvasImage, const Images::Image& signature)
{
	const Images::ImageInfo& canvasInfo = canvasImage.getImageInfo();
	const Images::ImageInfo& signatureInfo = signature.getImageInfo();

	const double SCALE_FACTOR = 0.25; // 25% of the larger side
	int targetWidth, targetHeight;

	// Scale based on the width or height, whichever is larger
	if (canvasInfo.width > canvasInfo.height)
	{
		targetWidth = static_cast<int>(canvasInfo.width * SCALE_FACTOR);
		targetHeight = static_cast<int>(signatureInfo.height * (targetWidth / static_cast<double>(signatureInfo.width)));
	}
	else
	{
		targetHeight = static_cast<int>(canvasInfo.height * SCALE_FACTOR);
		targetWidth = static_cast<int>(signatureInfo.width * (targetHeight / static_cast<double>(signatureInfo.height)));
	}

	Images::ImagePNG resizedSignature(signature.getFilepath(), targetWidth, targetHeight, 4);
	nearestNeighbor(signature, resizedSignature);

	const int X = canvasInfo.width - targetWidth;
	const int Y = canvasInfo.height - targetHeight;

	int x = 0;
	int x1 = 0;

	Images::Pixel pixel;

	for (int y = Y, y1 = 0; y < canvasInfo.height; y++, y1++)
	{
		for (x = X, x1 = 0; x < canvasInfo.width; x++, x1++)
		{
			pixel = resizedSignature.getPixel(x1, y1);
			if (pixel.alpha == 255)
				canvasImage.setPixel(x, y, resizedSignature.getPixel(x1, y1));
		}
	}

	canvasImage.rename(canvasImage.getFilename().substr(0, canvasImage.getFilename().find(".")) + "-signed");
	return canvasImage.saveImage();
}
} /* namespace ImageUtils */
