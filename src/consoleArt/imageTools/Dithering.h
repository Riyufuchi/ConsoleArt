//==============================================================================
// File       : Dithering.h
// Author     : riyufuchi
// Created on : Mar 18, 2025
// Last edit  : Nov 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_IMAGETOOLS_DITHERING_H_
#define CONSOLEART_IMAGETOOLS_DITHERING_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#include "../../images/utils/stb_image.h"
#include "../../images/utils/stb_image_write.h"
#include "../../images/utils/Pixels.hpp"

namespace ImageUtils
{
class Dithering
{
private:
	std::vector<consoleartlib::PixelRGB> minecraftPalette;
public:
	Dithering();
	virtual ~Dithering();
	consoleartlib::PixelRGB findClosestColor(uint8_t r, uint8_t g, uint8_t b);
	void ditherImage(std::string imagepath);
};
} /* namespace consoleart */
#endif /* CONSOLEART_IMAGETOOLS_DITHERING_H_ */
