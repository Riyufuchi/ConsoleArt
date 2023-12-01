//==============================================================================
// File       : ImageTools.h
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Dec 1, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGEUTILS_IMAGETOOLSCLI_H_
#define IMAGEUTILS_IMAGETOOLSCLI_H_

#include <iostream>

#include "../images/Image.h"

namespace ImageUtils
{
class ImageToolsCLI
{
public:
	ImageToolsCLI();
	virtual ~ImageToolsCLI();
	static void displayImageInfo(Images::Image* image);
};

} /* namespace ImageUtils */
#endif /* IMAGEUTILS_IMAGETOOLSCLI_H_ */
