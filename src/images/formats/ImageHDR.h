//==============================================================================
// File       : ImageHDR.h
// Author     : riyufuchi
// Created on : Nov 07, 2025
// Last edit  : Nov 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEHDR_H_
#define IMAGES_IMAGEHDR_H_

#include "../base/Image.h"

namespace Images
{

class ImageHDR: public Image
{
private:
	std::vector<float> pixelDataHDR;
public:
	ImageHDR(std::string filename, bool convert = true);
	virtual ~ImageHDR();
	PixelHDR getPixelHDR(int x, int y) const;
	void setPixelHDR(int x, int y, PixelHDR newPixel);
	void convertTo8bit();
	void convertFrom8bit();
	// Overrides
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};

} /* namespace Images */

#endif /* IMAGES_IMAGEHDR_H_ */
