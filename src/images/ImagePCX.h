//==============================================================================
// File       : ImagePCX.h
// Author     : Riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Nov 15, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _IMAGES_IMAGE_PCX_H_
#define _IMAGES_IMAGE_PCX_H_

#include <vector>
#include <iostream>

#include "Image.h"

namespace Images
{
class ImagePCX : public Image
{
public:
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
		PixelRGB palette[16]; // uint8_t palette[48] {0};    // Color palette (16 colors)
		uint8_t reserved1 {0};       // Reserved (always 0)
		uint8_t numOfColorPlanes {0}; // Number of color planes
		uint16_t bytesPerLine {0};  // Bytes per scanline
		uint16_t paletteType {0};   // Palette type (color or grayscale)
		uint16_t xResSourSysScrn {0} ;
		uint16_t yResSourSysScrn {0};
		uint8_t reserved2[54] {0};
	};
	#pragma pack(pop)
private:
	PCXHeader headerPCX;
	PixelRGB* paletteVGA;
	int BLUE_OFFSET;
	int ALPHA_OFFSET;
	void updateImage();
	void write24and32bitPCX(std::ofstream& outf) const;
public:
	ImagePCX(std::string filename);
	~ImagePCX();
	bool containsPalette() const;
	const PCXHeader& getHeader() const;
	bool saveImage(std::ofstream& stream) const;
	// Static
	static void checkHeader(const PCXHeader& headerPCX, const ImageInfo& image);
	static void readHeader(std::ifstream& stream, PCXHeader& headerPCX, ImageInfo& image);
	static void decodeRLE(std::ifstream& inf, std::vector<uint8_t>& imageData, const PCXHeader& headerPCX);
	static uint32_t calcFileEnd(std::ifstream& stream);
	static PixelRGB* readPaletteVGA(std::ifstream& inf, const uint32_t end);
	static bool isVGA(const PCXHeader& headerPCX);
	static bool loadImageDataVGA(std::ifstream& stream, std::vector<uint8_t>& imageData, PCXHeader& headerPCX, ImageInfo& image, std::string& errMsg, PixelRGB*& paletteVGA, const uint32_t start);
	static bool convertImageDataVGA(const std::vector<uint8_t>& imageData, std::vector<uint8_t>& pixelData, const ImageInfo& image, const PixelRGB* paletteVGA);
	// Overrides
	Pixel getPixel(int x, int y) const override;
	void setPixel(int x, int y, Pixel newPixel) override;
	bool saveImage() const override;
	void loadImage() override;
};
} /* namespace Images */
#endif /* IMAGES_IMAGEPCX_H_ */
