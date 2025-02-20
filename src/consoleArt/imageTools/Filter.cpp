//==============================================================================
// File       : Filter.cpp
// Author     : riyufuchi
// Created on : Feb 20, 2025
// Last edit  : Feb 20, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Filter.h"

namespace ImageUtils
{
Filter::Filter()
{
}
Filter::~Filter()
{
}
bool Filter::matrixFilter(Images::Image& image)
{
	if (!image)
		return false;
	const Images::ImageInfo& info = image.getImageInfo();
	Images::Pixel pixel;
	const double RED_FRACTION = 7/5;
	const double BLUE_FRACTION = 8/5;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			pixel.red = std::pow(pixel.red, RED_FRACTION);
			pixel.red = std::pow(pixel.blue, BLUE_FRACTION);
			image.setPixel(x,y, pixel);
		}
	}
	ImageTools::addToImageName(image, "-matrix");
	return image.saveImage();
}
} /* namespace ConsoleArt */
