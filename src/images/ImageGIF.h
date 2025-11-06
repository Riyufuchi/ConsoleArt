//==============================================================================
// File       : ImageGIF.h
// Author     : riyufuchi
// Created on : Nov 6, 2025
// Last edit  : Nov 6, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEGIF_H_
#define IMAGES_IMAGEGIF_H_

#include "Image.h"

namespace Images
{

class ImageGIF: public Image
{
private:
	std::vector<std::vector<uint8_t>> frames;
	std::vector<int> delays;
public:
	ImageGIF(const std::string& filepath);
	virtual ~ImageGIF();
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};

} /* namespace */

#endif /* IMAGES_IMAGEGIF_H_ */
