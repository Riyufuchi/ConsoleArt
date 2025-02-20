//==============================================================================
// File       : ImageTools.h
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGEUTILS_IMAGETOOLS_H_
#define IMAGEUTILS_IMAGETOOLS_H_

#include <iostream>

#include "../../images/Image.h"
#include "../../images/ImagePNG.h"

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
};

} /* namespace ImageUtils */
#endif /* IMAGEUTILS_IMAGETOOLS_H_ */
