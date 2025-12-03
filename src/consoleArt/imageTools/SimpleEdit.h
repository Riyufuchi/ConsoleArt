//==============================================================================
// File       : SimpleEdit.h
// Author     : riyufuchi
// Created on : Mar 21, 2025
// Last edit  : Nov 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_IMAGETOOLS_SIMPLEEDIT_H_
#define CONSOLEART_IMAGETOOLS_SIMPLEEDIT_H_

#include <cmath>

#include "../../images/formats/Formats.hpp"

namespace ImageUtils
{
class SimpleEdit
{
public:
	SimpleEdit();
	virtual ~SimpleEdit();
	static bool isPixelGray(int r, int g, int b);
	static bool removeGrayFromTexture(std::string originalPicture, std::string outputPicture);
	static bool removeGrayFromTexture(consoleartlib::Image& originalPicture);
	static bool overlayTextures(const consoleartlib::Image& bottomlayer, const consoleartlib::Image& overlay);
};
} /* namespace ImageUtils */
#endif /* CONSOLEART_IMAGETOOLS_SIMPLEEDIT_H_ */
