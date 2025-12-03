//==============================================================================
// File       : Filter.h
// Author     : riyufuchi
// Created on : Feb 20, 2025
// Last edit  : Nov 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_IMAGETOOLS_FILTER_H_
#define CONSOLEART_IMAGETOOLS_FILTER_H_

#include <cmath>

#include "../../images/base/Image.h"
#include "../cli/ProgressBarCLI.h"
#include "ImageTools.h"

namespace ImageUtils
{
class Filter
{
public:
	Filter();
	~Filter();
	static bool purplefier(consoleartlib::Image& image);
	static bool purplefierSoft(consoleartlib::Image& image);
	static bool purplefierShading(consoleartlib::Image& image);
	static bool purplefierShadingSoft(consoleartlib::Image& image);
	static bool matrixFilter(consoleartlib::Image& image);
};
} /* namespace consoleart */

#endif /* CONSOLEART_IMAGETOOLS_FILTER_H_ */
