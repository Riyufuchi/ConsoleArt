//==============================================================================
// File       : IMultiPage.hpp
// Author     : riyufuchi
// Created on : Nov 16, 2025
// Last edit  : Nov 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IAnimated_HPP_
#define IMAGES_IAnimated_HPP_

#include "IMultiPage.hpp"

namespace Images
{
class IAnimated
{
public:
	IAnimated() = default;
	virtual ~IAnimated() = default;
	virtual int getFrameDelay(size_t index) const = 0;
};
}

#endif /* IMAGES_IMULTIPAGE_HPP_ */
