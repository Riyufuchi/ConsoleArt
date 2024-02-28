//==============================================================================
// File       : ImagePCX.h
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Feb 22, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGEPCX_H_
#define IMAGES_IMAGEPCX_H_

#include <vector>
#include <iostream>

#include "Image.h"

namespace Images
{
class ImagePCX : public Image
{
private:
	#pragma pack(push, 1)
	struct PCXHeader
	{
		uint8_t file_type {0x0A};   // PCX identifier (always 0x0A)
		uint8_t version {0};        // PCX version (0-5)
		uint8_t encoding {0};       // Compression type
		uint8_t bitsPerPixel {0};   // Number of bits per pixel per plane
		uint16_t xMin {0};
		uint16_t yMin {0};    // Image dimensions (left-top corner)
		uint16_t xMax {0};
		uint16_t yMax {0};    // Image dimensions (right-bottom corner)
		uint16_t horizontalDPI {0}; // Horizontal resolution
		uint16_t verticalDPI {0};   // Vertical resolution
		uint8_t palette[48] {0};    // Color palette (16 colors)
		uint8_t reserved1 {0};       // Reserved (always 0)
		uint8_t numOfColorPlanes {0}; // Number of color planes
		uint16_t bytesPerLine {0};  // Bytes per scanline
		uint16_t paletteType {0};   // Palette type (color or grayscale)
		uint16_t xResSourSysScrn {0} ;
		uint16_t yResSourSysScrn {0};
		uint8_t reserved2[54] {0};
	} headerPCX;
	#pragma pack(pop)
	std::vector<uint8_t> imageData;
	std::vector<Pixel> pixels;
	ImageInfo info;
	int positionBase;
	void readPCX();
	void readImageData(std::ifstream& inf);
	//void make24bitPCX();
	//void make32bitPCX();
	void updateImage();
	void write24and32bitPCX(std::ofstream& outf);
	void checkHeader();
public:
	ImagePCX(std::string filename);
	~ImagePCX();
	ImageInfo getImageInfo() override;
	Pixel getPixel(int x, int y) override;
	void setPixel(int x, int y, Pixel newPixel) override;
	const bool saveImage() override;

};
} /* namespace Images */
#endif /* IMAGES_IMAGEPCX_H_ */
