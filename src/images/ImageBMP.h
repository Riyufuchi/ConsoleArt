//============================================================================
// Name        : ImageBMP
// Author      : Riyufuchi
// Created on  : Jul 17, 2020
// Last Edit   : Feb 17, 2025
// Description : This class loads uncompressed 24 or 32 bit bitmap image
//============================================================================

#ifndef _IMAGE_BMP_H_
#define _IMAGE_BMP_H_

#include <iostream>
#include <string>
#include <vector>

#include "Image.h"

namespace Images
{
class ImageBMP : public Image
{
private:
	#pragma pack(push, 1)
		struct BMPFileHeader
		{
			uint16_t file_type{0x4D42}; //File type - bitmap is 0x4D42
			uint32_t file_size{0}; //Size of the file (in bytes)
			uint16_t reserved1{0};
			uint16_t reserved2{0}; //Reserved - always 0
			uint32_t offset_data{0}; //Bytes from the beginning of the file
		} headerBMP;
		struct BMPInfoHeader
		{
			uint32_t size{0}; //Size of this header in bytes
			int32_t width{0}; //width of bitmap in pixels
			int32_t height{0}; //height of bitmap in pixel (if positive, bottom-up, with origin in lower left corner and if negative, top-down, with origin in upper left corner
			uint16_t planes{1}; //No. of planes for the target device, this is always 1
			uint16_t bit_count{0}; //No. of bits per pixel
			uint32_t compression{0}; //0 or 3 - uncompressed
			uint32_t size_image{0}; //0 - for uncompressed images
			int32_t x_pixels_per_meter{0};
			int32_t y_pixels_per_meter{0};
			uint32_t colors_used{0}; //No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
			uint32_t colors_important{0}; //No. of colors used for displaying the bitmap. If 0 all colors are required
		} bmp_info_header;
		struct BMPColorHeader
		{
			uint32_t red_mask{0x00ff0000}; //Bit mask for the red channel
			uint32_t green_mask{0x0000ff00}; //Bit mask for the green channel
			uint32_t blue_mask{0x000000ff}; //Bit mask for the blue channel
			uint32_t alpha_mask{0xff000000}; //Bit mask for the alpha channel
			uint32_t color_space_type{0x73524742}; //Default "sRGB" (0x73524742)
			uint32_t unused[16]{0}; //Unused data for sRGB color space
		} bmp_color_header;
	#pragma pack(pop)
	uint32_t row_stride;
	// Methods
	void checkHeader(std::ifstream& inf);
	void readImageData(std::ifstream& inf);
	bool checkColorHeader(BMPColorHeader &bmp_color_header, std::string* msg);
	uint32_t makeStrideAligned(uint32_t align_stride);
public:
	ImageBMP(std::string filename);
	bool saveImage() const override;
	void loadImage() override;
	// Setters
	void setPixel(int x, int y, Pixel newPixel) override;
	// Getters
	Pixel getPixel(int x, int y) const override;
	uint8_t getRed(int x, int y) const;
	uint8_t getGreen(int x, int y) const;
	uint8_t getBlue(int x, int y) const;
	uint8_t getAplha(int x, int y) const;
	~ImageBMP();
};
}
#endif
