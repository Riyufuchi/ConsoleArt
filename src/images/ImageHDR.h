//==============================================================================
// File       : ImageHDR.h
// Author     : riyufuchi
// Created on : Nov 7, 2025
// Last edit  : Nov 7, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEHDR_H_
#define IMAGES_IMAGEHDR_H_

#include "Image.h"

namespace Images
{

class ImageHDR: public Image
{
public:
	ImageHDR(std::string filename);
	virtual ~ImageHDR();
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};

} /* namespace Images */

#endif /* IMAGES_IMAGEHDR_H_ */
