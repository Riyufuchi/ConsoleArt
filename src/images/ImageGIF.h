//==============================================================================
// File       : ImageGIF.h
// Author     : riyufuchi
// Created on : Nov 06, 2025
// Last edit  : Nov 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEGIF_H_
#define IMAGES_IMAGEGIF_H_

#include "Image.h"
#include "IAnimated.hpp"

namespace Images
{

class ImageGIF: public Image, public IAnimated, public IMultiPage
{
private:
	std::vector<std::vector<uint8_t>> frames;
	std::vector<int> delays;
	size_t selectedFrameIndex;
public:
	ImageGIF(const std::string& filepath);
	~ImageGIF();
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
	virtual void selectPage(size_t index) override;
	virtual size_t getSelectedPageIndex() const override;
	virtual size_t getPageCount() const override;
	const std::vector<uint8_t>& getFrame(int index) const;
	virtual int getFrameDelay(size_t index) const override;
	bool spitIntoPNGs() const;
	//TODO: bool addFrame(const Image& frame, int index = 0);
	//TODO: bool removeFrame(int index);
};

} /* namespace */

#endif /* IMAGES_IMAGEGIF_H_ */
