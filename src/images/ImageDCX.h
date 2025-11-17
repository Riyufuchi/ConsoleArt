//==============================================================================
// File       : ImageDCX.h
// Author     : riyufuchi
// Created on : Nov 13, 2025
// Last edit  : Nov 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEDCX_H_
#define IMAGES_IMAGEDCX_H_

#include "ImagePCX.h"
#include "IMultiPage.hpp"

namespace Images
{
struct ImageRange
{
	uint32_t start = 0;  // byte offset where image/header begins
	uint32_t end   = 0;  // byte offset where image/header ends (exclusive)
	uint32_t size() const { return end - start; }
};
class ImageDCX: public Image, public IMultiPage
{
private:
	size_t selectedPage;
	int numOfPages;
	ImagePCX::HeaderPCX headerPCX;
	std::vector<ImageRange> ranges;
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
	virtual void selectPage(size_t index) override final;
	const ImagePCX::PagePCX& getSelectedPage() const;
	virtual size_t getSelectedPageIndex() const override final;
	virtual size_t getPageCount() const override;
	void addImage(ImagePCX::PagePCX image);
};

} /* namespace Images */

#endif /* IMAGES_IMAGEDCX_H_ */
