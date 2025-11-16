//==============================================================================
// File       : ImagePCX.h
// Author     : Riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Nov 16, 2025
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
	struct HeaderPCX
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
	struct PagePCX
	{
		HeaderPCX header;
		ImageInfo image;
		std::vector<unsigned char> pixelData;
		std::string msg { "OK" };
		PixelRGB* palette = nullptr;
	};
private:
	HeaderPCX headerPCX;
	PixelRGB* paletteVGA;
	int BLUE_OFFSET;
	int ALPHA_OFFSET;
	void updateImage();
	static void decodeRLE(std::ifstream& inf, std::vector<uint8_t>& imageData, const HeaderPCX& headerPCX, const uint32_t lenght);
	static bool loadImageDataVGA(std::ifstream& stream, std::vector<uint8_t>& imageData,PagePCX& pcx, const uint32_t start, const uint32_t end);
	static bool convertImageDataVGA(const std::vector<uint8_t>& imageData, PagePCX& pcx);
	static bool readVGA(std::ifstream& inf, PagePCX& pcx, const uint32_t end);
	static void writePlanarPixalData(std::ofstream& stream, const std::vector<unsigned char>& pixelData);
public:
	ImagePCX(std::string filename);
	~ImagePCX();
	const HeaderPCX& getHeader() const;
	PagePCX convertToPage() const;
	// Static functions
	static void checkHeader(const HeaderPCX& headerPCX, const ImageInfo& image);
	static void readHeader(std::ifstream& stream, HeaderPCX& headerPCX, ImageInfo& image);
	static uint32_t calcFileEnd(std::ifstream& stream);
	static bool readPCX(std::ifstream& stream, PagePCX& pcx, const uint32_t start, const uint32_t end);
	static bool savePCX(std::ofstream& stream, const PagePCX& pcx);
	static bool isVGA(const HeaderPCX& headerPCX);
	// Overrides
	Pixel getPixel(int x, int y) const override;
	void setPixel(int x, int y, Pixel newPixel) override;
	bool saveImage() const override;
	void loadImage() override;
};
} /* namespace Images */
#endif /* IMAGES_IMAGEPCX_H_ */
