//==============================================================================
// File       : Filter.h
// Author     : riyufuchi
// Created on : Feb 20, 2025
// Last edit  : Feb 20, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_IMAGETOOLS_FILTER_H_
#define CONSOLEART_IMAGETOOLS_FILTER_H_

#include <cmath>

#include "../../images/Image.h"
#include "ImageTools.h"

namespace ImageUtils
{
class Filter
{
public:
	Filter();
	~Filter();
	static bool matrixFilter(Images::Image& image);
};
} /* namespace ConsoleArt */

#endif /* CONSOLEART_IMAGETOOLS_FILTER_H_ */
