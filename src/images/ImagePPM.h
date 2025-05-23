//==============================================================================
// File       : ImagePPM.h
// Author     : riyufuchi
// Created on : Mar 17, 2024
// Last edit  : May 9, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _IMAGES_IMAGE_PPM_H_
#define _IMAGES_IMAGE_PPM_H_

#include <string>
#include <sstream>

#include "Image.h"

#include "DataUtils.h"

namespace Images
{
class ImagePPM : public Image
{
private:
	struct HeaderPPM
	{
		std::string format{"P3"};
		int width{3};
		int height{3};
		short maxColorVal{255};
	} headerPPM;
public:
	ImagePPM(std::string filename);
	ImagePPM(std::string filename, int width, int height);
	~ImagePPM();
	void virtualArtistLegacy();
	// Overrides
	Pixel getPixel(int x, int y) const override;
	void setPixel(int x, int y, Pixel newPixel) override;
	bool saveImage() const override;
	void loadImage() override;
};
} /* namespace Images */
#endif /* IMAGES_IMAGEPPM_H_ */
