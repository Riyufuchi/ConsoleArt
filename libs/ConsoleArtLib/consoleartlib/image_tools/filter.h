//==============================================================================
// File       : Filter.h
// Author     : riyufuchi
// Created on : Feb 20, 2025
// Last edit  : Dec 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_IMAGETOOLS_FILTER_H_
#define CONSOLEART_IMAGETOOLS_FILTER_H_

#include <cmath>

#include "../images/base/image.h"
#include "image_tools.h"

namespace consoleartlib::filter
{
bool purplefier(consoleartlib::Image& image);
bool purplefierSoft(consoleartlib::Image& image);
bool purplefierShading(consoleartlib::Image& image);
bool purplefierShadingSoft(consoleartlib::Image& image);
bool matrixFilter(consoleartlib::Image& image);
}
#endif
