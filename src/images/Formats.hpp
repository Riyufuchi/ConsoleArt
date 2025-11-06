//==============================================================================
// File       : Formats.hpp
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Nov 06, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_FORMATS_HPP_
#define IMAGES_FORMATS_HPP_

#include "Image.h"
#include "ImageBMP.h"
#include "ImagePCX.h"
#include "ImagePPM.h"
#include "ImagePNG.h"
#include "ImageJPG.h"
#include "ImageGIF.h"

namespace Images
{
enum ImageType
{
	BMP,
	PCX,
	PPM,
	PNG,
	JPG,
	GIF
};
}
#endif /* IMAGES_FORMATS_HPP_ */
