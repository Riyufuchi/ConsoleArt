//==============================================================================
// File       : ImageTools.cpp
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Feb 14, 2025
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
	return -2;
}
} /* namespace ImageUtils */
