//==============================================================================
// File       : ImageTools.h
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Feb 14, 2025
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGEUTILS_IMAGETOOLS_H_
#define IMAGEUTILS_IMAGETOOLS_H_

#include <iostream>

#include "../../images/Image.h"

namespace ImageUtils
{
class ImageTools
{
public:
	ImageTools();
	virtual ~ImageTools();
	static int compareImages(const Images::Image& image1, const Images::Image& image2);
};

} /* namespace ImageUtils */
#endif /* IMAGEUTILS_IMAGETOOLS_H_ */
