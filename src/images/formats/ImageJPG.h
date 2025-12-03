//==============================================================================
// File       : ImageJPG.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Nov 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef IMAGES_IMAGEJPG_H_
#define IMAGES_IMAGEJPG_H_

#include "../base/Image.h"

namespace consoleartlib
{
class ImageJPG : public Image
{
public:
	ImageJPG(std::string filepath);
	ImageJPG(std::string filepath, int width, int height, int channels);
	~ImageJPG();
	virtual consoleartlib::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, consoleartlib::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
};
} /* namespace consoleartlib */
#endif /* IMAGES_IMAGEJPG_H_ */
