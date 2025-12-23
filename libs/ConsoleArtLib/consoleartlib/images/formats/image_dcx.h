//==============================================================================
// File       : ImageDCX.h
// Author     : riyufuchi
// Created on : Nov 13, 2025
// Last edit  : Dec 19, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef IMAGES_IMAGEDCX_H_
#define IMAGES_IMAGEDCX_H_

#include "image_pcx.h"
#include "../interfaces/imulti_page.hpp"

namespace consoleartlib
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
	ImageDCX(const std::string& filename);
	ImageDCX(const std::string& filename, int numberOfPages);
	virtual ~ImageDCX();
	virtual consoleartlib::Pixel getPixel(int x, int y) const override;
	virtual void setPixel(int x, int y, consoleartlib::Pixel newPixel) override;
	virtual bool saveImage() const override;
	virtual void loadImage() override;
	//
	virtual void selectPage(size_t index) override final;
	const ImagePCX::PagePCX& getSelectedPage() const;
	virtual size_t getSelectedPageIndex() const override final;
	virtual size_t getPageCount() const override;
	void addImage(ImagePCX::PagePCX image);
};

} /* namespace consoleartlib */

#endif /* IMAGES_IMAGEDCX_H_ */
