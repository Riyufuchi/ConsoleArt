//==============================================================================
// File       : SimpleEdit.h
// Author     : riyufuchi
// Created on : Mar 21, 2025
// Last edit  : Dec 20, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_IMAGETOOLS_SIMPLEEDIT_H_
#define CONSOLEART_IMAGETOOLS_SIMPLEEDIT_H_

#include <cmath>

#include "../image_formats.hpp"

namespace consoleartlib::simple_edit
{
bool isPixelGray(int r, int g, int b);
bool removeGrayFromTexture(const std::string& originalPicture, const std::string& outputPicture);
bool removeGrayFromTexture(consoleartlib::Image& originalPicture);
bool overlayTextures(const consoleartlib::Image& bottomlayer, const consoleartlib::Image& overlay);
}
#endif
