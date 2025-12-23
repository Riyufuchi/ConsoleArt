//==============================================================================
// File       : ImagePNG.h
// Author     : riyufuchi
// Created on : Feb 17, 2025
// Last edit  : Dec 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef IMAGES_IMAGEPNG_H_
#define IMAGES_IMAGEPNG_H_

#include <iostream>
#include <string.h>

#include "../base/image.h"
//#include "../utils/stb_image.h"

namespace consoleartlib
{
class ImagePNG: public Image
{
public:
	ImagePNG(const std::string& filepath);
	ImagePNG(const std::string& filepath, int width, int height, int channels);
	~ImagePNG();
	virtual consoleartlib::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, consoleartlib::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};

} /* namespace consoleartlib */

#endif /* IMAGES_IMAGEPNG_H_ */
