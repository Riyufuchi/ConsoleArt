//==============================================================================
// File       : Filter.cpp
// Author     : riyufuchi
// Created on : Feb 20, 2025
// Last edit  : Feb 21, 2025
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
bool Filter::purplefier(Images::Image& image)
{
	if (!image)
		return false;
	const Images::ImageInfo& info = image.getImageInfo();
	Images::Pixel pixel;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			pixel.red = pixel.blue;
			image.setPixel(x,y, pixel);
		}
	}
	ImageTools::addToImageName(image, "-purplefied");
	return image.saveImage();
}
bool Filter::purplefierShading(Images::Image& image)
{
	if (!image)
		return false;
	const Images::ImageInfo& info = image.getImageInfo();
	Images::Pixel pixel;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			pixel.red = pixel.blue;
			if (pixel.red < pixel.green)
				pixel.green = pixel.red;
			image.setPixel(x,y, pixel);
		}
	}
	ImageTools::addToImageName(image, "-purplefiedShaded");
	return image.saveImage();
}
bool Filter::purplefierSoft(Images::Image& image)
{
	if (!image)
		return false;
	const Images::ImageInfo& info = image.getImageInfo();
	ConsoleArt::ProgressBarCLI bar(info.height);
	Images::Pixel pixel;
	bar.drawProgressBar();
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			if (pixel.blue < pixel.green)
			{
				pixel.green = pixel.blue / 2;
			}
			pixel.red = pixel.blue;
			image.setPixel(x,y, pixel);
		}
		bar.drawProgressBar();
	}
	std::cout << "\n";
	ImageTools::addToImageName(image, "-purplefiedSoft");
	return image.saveImage();
}
bool Filter::matrixFilter(Images::Image& image)
{
	if (!image)
		return false;
	const Images::ImageInfo& info = image.getImageInfo();
	const double RED_FRACTION = 7 / 5.0;
	const double BLUE_FRACTION = 8 / 5.0;
	const unsigned char MAX_COLOR = 255;
	Images::Pixel pixel;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			pixel.red = std::pow((double)pixel.red / MAX_COLOR, RED_FRACTION) * MAX_COLOR;
			pixel.blue = std::pow((double)pixel.blue / MAX_COLOR, BLUE_FRACTION) * MAX_COLOR;
			image.setPixel(x,y, pixel);
		}
	}
	ImageTools::addToImageName(image, "-matrix");
	return image.saveImage();
}
} /* namespace ConsoleArt */
