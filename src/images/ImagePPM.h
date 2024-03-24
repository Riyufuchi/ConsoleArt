//==============================================================================
// File       : ImagePPM.h
// Author     : riyufuchi
// Created on : Mar 17, 2024
// Last edit  : Mar 24, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _IMAGES_IMAGE_PPM_H_
#define _IMAGES_IMAGE_PPM_H_

#include <string>
#include <vector>
#include <sstream>

#include "Image.h"

#include "../inc/DataUtils.h"

namespace Images
{
class ImagePPM: public Image
{
private:
	struct HeaderPPM
	{
		std::string format{"P3"};
		int width{3};
		int height{3};
		short maxColorVal{255};
	} headerPPM;
	std::vector<Pixel> imageData;
	int positionBase;
public:
	ImagePPM(std::string filename);
	ImagePPM(std::string filename, int width, int height);
	~ImagePPM();
	void virtualArtistLegacy();
	// Overrides
	ImageInfo getImageInfo() const override;
	Pixel getPixel(int x, int y) override;
	void setPixel(int x, int y, Pixel newPixel) override;
	const bool saveImage() override;
	void loadImage() override;
};
} /* namespace Images */
#endif /* IMAGES_IMAGEPPM_H_ */
