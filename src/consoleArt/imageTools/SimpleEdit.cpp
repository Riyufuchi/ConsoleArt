//==============================================================================
// File       : SimpleEdit.cpp
// Author     : riyufuchi
// Created on : Mar 21, 2025
// Last edit  : Mar 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "SimpleEdit.h"

namespace ImageUtils
{
SimpleEdit::SimpleEdit()
{
}

SimpleEdit::~SimpleEdit()
{
}

bool SimpleEdit::overlayTextures(const Images::Image& bottomlayer, const Images::Image& overlay)
{
	if (!(bottomlayer && overlay))
		return false;
	if (overlay.getFilename() == bottomlayer.getFilename())
		return false;
	if (bottomlayer > overlay)
		return false;
	Images::ImagePNG resultImage(bottomlayer.getFilename().substr(0, bottomlayer.getFilename().size() - 4) + "_" + overlay.getFilename(), bottomlayer.getWidth(), bottomlayer.getHeight(), bottomlayer.getBits()/8);
	Images::Pixel pixel;
	for(int y = 0; y < bottomlayer.getHeight(); y++)
	{
		for (int x = 0; x < bottomlayer.getWidth(); x++)
		{
			pixel = overlay.getPixel(x, y);
			if (pixel.alpha > 0)
				resultImage.setPixel(x, y, pixel);
			else
				resultImage.setPixel(x, y, bottomlayer.getPixel(x, y));
		}
	}
	return resultImage.saveImage();
}

bool SimpleEdit::isPixelGray(int r, int g, int b)
{
	return std::abs(r - g) < 10 && std::abs(r - b) < 10 && std::abs(g - b) < 10;
}

bool SimpleEdit::removeGrayFromTexture(std::string originalPicturePath, std::string outputPicturePath)
{
	Images::ImagePNG originalTexture(originalPicturePath);
	if (!originalTexture)
		return false;
	Images::ImagePNG targetTexture(outputPicturePath, originalTexture.getWidth(), originalTexture.getHeight(), originalTexture.getBits() / 8);
	Images::Pixel pixel;
	for(int y = 0; y < originalTexture.getHeight(); y++)
	{
		for (int x = 0; x < originalTexture.getWidth(); x++)
		{
			pixel = originalTexture.getPixel(x, y);
			if (isPixelGray(pixel.red, pixel.green, pixel.blue))
				pixel.alpha = 0;
			targetTexture.setPixel(x, y, pixel);
		}
	}
	return targetTexture.saveImage();
}

bool SimpleEdit::removeGrayFromTexture(Images::Image& originalTexture)
{
	if (!originalTexture)
		return false;
	Images::Pixel pixel;
	for(int y = 0; y < originalTexture.getHeight(); y++)
	{
		for (int x = 0; x < originalTexture.getWidth(); x++)
		{
			pixel = originalTexture.getPixel(x, y);
			if (isPixelGray(pixel.red, pixel.green, pixel.blue))
			{
				pixel.alpha = 0;
				originalTexture.setPixel(x, y, pixel);
			}
		}
	}
	return originalTexture.saveImage();
}

} /* namespace ImageUtils */
