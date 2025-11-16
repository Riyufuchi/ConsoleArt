//==============================================================================
// File       : ImageDCX.h
// Author     : riyufuchi
// Created on : Nov 13, 2025
// Last edit  : Nov 13, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEDCX_H_
#define IMAGES_IMAGEDCX_H_

#include "ImagePCX.h"

namespace Images
{
struct ImageRange
{
	uint32_t start = 0;  // byte offset where image/header begins
	uint32_t end   = 0;  // byte offset where image/header ends (exclusive)
	uint32_t size() const { return end - start; }
};
class ImageDCX: public Image
{
private:
	std::vector<ImageRange> ranges;
	int selectedPage;
	int numOfPages;
	std::vector<ImagePCX::PagePCX> pages;
public:
	ImageDCX(std::string filename);
	ImageDCX(std::string filename, int numberOfPages);
	virtual ~ImageDCX();
	virtual Images::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, Images::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
	//
	void setPage(size_t index);
	const ImagePCX::PagePCX& getSelectedPage();
	//void addImage(ImagePCX* image);
	//ImagePCX* getImage();
};

} /* namespace Images */

#endif /* IMAGES_IMAGEDCX_H_ */
