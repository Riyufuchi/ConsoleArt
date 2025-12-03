//==============================================================================
// File       : ImageHDR.h
// Author     : riyufuchi
// Created on : Nov 07, 2025
// Last edit  : Nov 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef IMAGES_IMAGEHDR_H_
#define IMAGES_IMAGEHDR_H_

#include "../base/Image.h"

namespace consoleartlib
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
	virtual consoleartlib::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, consoleartlib::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};

} /* namespace consoleartlib */

#endif /* IMAGES_IMAGEHDR_H_ */
