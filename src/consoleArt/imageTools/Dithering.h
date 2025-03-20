//==============================================================================
// File       : Dithering.h
// Author     : riyufuchi
// Created on : Mar 18, 2025
// Last edit  : Mar 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_IMAGETOOLS_DITHERING_H_
#define CONSOLEART_IMAGETOOLS_DITHERING_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#include "../../include/stb_image.h"
#include "../../include/stb_image_write.h"
#include "../../images/Pixels.hpp"

namespace ImageUtils
{
class Dithering
{
private:
	std::vector<Images::PixelRGB> minecraftPalette;
public:
	Dithering();
	virtual ~Dithering();
	Images::PixelRGB findClosestColor(uint8_t r, uint8_t g, uint8_t b);
	void ditherImage(std::string imagepath);
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_IMAGETOOLS_DITHERING_H_ */
