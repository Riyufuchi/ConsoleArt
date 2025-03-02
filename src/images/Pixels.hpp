//==============================================================================
// File       : Pixels.hpp
// Author     : riyufuchi
// Created on : Mar 24, 2024
// Last edit  : Mar 24, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_PIXELS_HPP_
#define IMAGES_PIXELS_HPP_

#include <cstdint>

namespace Images
{
enum PixelByteOrder
{
	RGBA,
	BGRA
};
struct PixelRGB
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};
struct Pixel
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha {255};
};
}
#endif /* IMAGES_PIXELS_HPP_ */
