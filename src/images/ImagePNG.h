//==============================================================================
// File       : ImagePNG.h
// Author     : riyufuchi
// Created on : Feb 17, 2025
// Last edit  : Feb 17, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEPNG_H_
#define IMAGES_IMAGEPNG_H_

#include <iostream>
#include "Image.h"

namespace Images
{
class ImagePNG: public Image
{
private:
	unsigned char* imageData;
	int CHANNELS;
public:
	ImagePNG(std::string filepath);
	~ImagePNG();
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};

} /* namespace Images */

#endif /* IMAGES_IMAGEPNG_H_ */
