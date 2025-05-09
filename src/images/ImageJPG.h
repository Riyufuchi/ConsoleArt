//==============================================================================
// File       : ImageJPG.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : May 9, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEJPG_H_
#define IMAGES_IMAGEJPG_H_

#include "Image.h"

namespace Images
{
class ImageJPG : public Image
{
public:
	ImageJPG(std::string filepath);
	ImageJPG(std::string filepath, int width, int height, int channels);
	~ImageJPG();
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};
} /* namespace Images */
#endif /* IMAGES_IMAGEJPG_H_ */
