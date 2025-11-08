//==============================================================================
// File       : ImageTGA.h
// Author     : riyufuchi
// Created on : Nov 7, 2025
// Last edit  : Nov 7, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGETGA_H_
#define IMAGES_IMAGETGA_H_

#include "Image.h"

namespace Images
{

class ImageTGA: public Image
{
public:
	ImageTGA(std::string filename);
	virtual ~ImageTGA() = default;
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};

} /* namespace Images */

#endif /* IMAGES_IMAGETGA_H_ */
