//==============================================================================
// File       : Filter.cpp
// Author     : riyufuchi
// Created on : Feb 20, 2025
// Last edit  : Nov 20, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
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
bool Filter::purplefier(consoleartlib::Image& image)
{
	if (!image)
		return false;
	const consoleartlib::ImageInfo& info = image.getImageInfo();
	consoleartlib::Pixel pixel;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			pixel.red = pixel.blue;
			image.setPixel(x,y, pixel);
		}
	}
	return (image >> "-purplefied").saveImage();
}
bool Filter::purplefierSoft(consoleartlib::Image& image)
{
	if (!image)
		return false;
	const consoleartlib::ImageInfo& info = image.getImageInfo();
	consoleart::ProgressBarCLI bar(info.height);
	consoleartlib::Pixel pixel;
	bar.drawProgressBar();
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			pixel.red = static_cast<uint16_t>(pixel.blue + pixel.red) / 2;
			pixel.blue = pixel.red;
			if (pixel.blue < pixel.green)
			{
				pixel.green = static_cast<uint16_t>(pixel.blue + pixel.red + pixel.green) / 3;
				pixel.red = pixel.green;
				pixel.blue = pixel.green;
			}
			image.setPixel(x,y, pixel);
		}
		bar.drawProgressBar();
	}
	std::cout << "\n";
	return (image >> "-purplefiedSoft").saveImage();
}
bool Filter::purplefierShading(consoleartlib::Image& image)
{
	if (!image)
		return false;
	const consoleartlib::ImageInfo& info = image.getImageInfo();
	consoleartlib::Pixel pixel;
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
	return (image >> "-purplefiedShaded").saveImage();
}
bool Filter::purplefierShadingSoft(consoleartlib::Image& image)
{
	if (!image)
		return false;
	const consoleartlib::ImageInfo& info = image.getImageInfo();
	consoleart::ProgressBarCLI bar(info.height);
	consoleartlib::Pixel pixel;
	bar.drawProgressBar();
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			pixel = image.getPixel(x, y);
			if (pixel.blue < pixel.green)
			{
				pixel.green = static_cast<uint16_t>(pixel.blue + pixel.red + pixel.green) / 3;
				pixel.red = pixel.green;
				pixel.blue = pixel.green;
			}
			else
			{
				pixel.red = static_cast<uint16_t>(pixel.blue + pixel.red) / 2;
			}
			image.setPixel(x,y, pixel);
		}
		bar.drawProgressBar();
	}
	std::cout << "\n";
	return (image >> "-purplefiedShadedSoft").saveImage();
}
bool Filter::matrixFilter(consoleartlib::Image& image)
{
	if (!image)
		return false;
	const consoleartlib::ImageInfo& info = image.getImageInfo();
	const double RED_FRACTION = 7 / 5.0;
	const double BLUE_FRACTION = 8 / 5.0;
	const unsigned char MAX_COLOR = 255;
	consoleartlib::Pixel pixel;
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
	return (image >> "-matrix").saveImage();
}
} /* namespace consoleart */
