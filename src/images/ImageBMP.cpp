﻿//============================================================================
// Name        : ImageBMP
// Author      : Riyufuchi
// Created on  : Jul 17, 2020
// Last Edited : Feb 14, 2025
// Description : This class is responsible for loading uncompressed 24-bit or 32-bit BMP image files.
//               It provides functionality to read BMP files, including the file header, BMP information,
//               and color data. The image must have the origin in the bottom left corner.
//============================================================================

#include "ImageBMP.h"

namespace Images
{
ImageBMP::ImageBMP(std::string filename) : Image(filename)
{
	loadImage();
	imageInfo.name = this->filename;
	imageInfo.width = bmp_info_header.width;
	imageInfo.height = bmp_info_header.height;
	imageInfo.file_type = headerBMP.file_type;
	imageInfo.bits = bmp_info_header.bit_count;
	this->CHANNELS = bmp_info_header.bit_count / 8;
}

void ImageBMP::loadImage()
{
	std::ifstream inf(filepath, std::ios::in);
	if (!inf)
	{
		this->fileStatus = "Unable to open file: " + filename;
		return;
	}
	try
	{
		checkHeader(inf);
	}
	catch (std::runtime_error& e)
	{
		this->fileStatus = e.what();
		return;
	}
	readImageData(inf);
	// Check for image orientation
	this->inverted = bmp_info_header.height > 0; // Origin is in bottom left corner, if this turns to be false
	this->fileState = OK;
}
void ImageBMP::readImageData(std::ifstream& inf)
{
	headerBMP.file_size = headerBMP.offset_data;
	pixelData.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);
	if (bmp_info_header.width % 4 == 0)
	{
		inf.read(reinterpret_cast<char*>(pixelData.data()), pixelData.size());
		headerBMP.file_size += pixelData.size();
	}
	else
	{
		row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
		uint32_t new_stride = makeStrideAligned(4);
		std::vector<uint8_t> padding_row(new_stride - row_stride);
		for (int y = 0; y < bmp_info_header.height; ++y)
		{
			inf.read(reinterpret_cast<char*>(pixelData.data() + row_stride * y), row_stride);
			inf.read(reinterpret_cast<char*>(padding_row.data()), padding_row.size());
		}
		headerBMP.file_size += pixelData.size() + bmp_info_header.height * padding_row.size();
	}
}
void ImageBMP::checkHeader(std::ifstream& inf)
{
	inf.read(reinterpret_cast<char*>(&headerBMP), sizeof(headerBMP)); //Reads and fill our file_header struct with data
	if (headerBMP.file_type != 0x4D42)
		throw std::runtime_error("Error: Unrecognized format " + filename.substr(getFilename().find_last_of(".")));
	//BMP info and colors
	inf.read(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));
	if (bmp_info_header.bit_count != 24 && bmp_info_header.bit_count != 32)
		throw std::runtime_error("This reader dosn't support " + std::to_string( bmp_info_header.bit_count) + "-bit images.");
	if (bmp_info_header.bit_count == 32)
	{
		if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader)))
		{
			inf.read(reinterpret_cast<char*>(&bmp_color_header), sizeof(bmp_color_header));
			std::string msg = "No Error";
			if (checkColorHeader(bmp_color_header, &msg))
				throw std::runtime_error(msg); //checkColorHeader prints addional information
		}
		else
		{
			throw std::runtime_error("Error: The  " + filename + " doesn't seem to contain bit mask information");
		}
	}
	inf.seekg(headerBMP.offset_data, inf.beg); // Position the stream at the beginning of the image data
	if (bmp_info_header.bit_count == 32)
	{
		bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
		headerBMP.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
	}
	else
	{
		bmp_info_header.size = sizeof(BMPInfoHeader);
		headerBMP.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
	}
}
// This function checks if the provided BMPColorHeader matches the expected color format
bool ImageBMP::checkColorHeader(BMPColorHeader& bmp_color_header, std::string* msg)
{
	BMPColorHeader expected_color_header; // Create an expected BMPColorHeader with default values
	// Compare the color masks (red, blue, green, and alpha) in the provided header
	// with the expected header. If any mask differs, it's an unexpected format.
	if (expected_color_header.red_mask != bmp_color_header.red_mask ||
		expected_color_header.blue_mask != bmp_color_header.blue_mask ||
		expected_color_header.green_mask != bmp_color_header.green_mask ||
		expected_color_header.alpha_mask != bmp_color_header.alpha_mask)
	{
		*msg = "Unexpected color mask format!\nThe program expects the pixel data to be in the BGRA format";
		return true;
	}
	// Compare the color space type in the provided header with the expected type (sRGB).
	if (expected_color_header.color_space_type != bmp_color_header.color_space_type)
	{
		*msg = "Unexpected color space type! The program expects sRGB values";
		return true;
	}
	return false;
}
uint32_t ImageBMP::makeStrideAligned(uint32_t align_stride)
{
	uint32_t new_stride = row_stride;
	while (new_stride % align_stride != 0)
	{
		new_stride++;
	}
	return new_stride;
}

Pixel ImageBMP::getPixel(int x, int y)
{
	positionBase = CHANNELS * (y * bmp_info_header.width + x);
	if (CHANNELS == 4)
		return {pixelData[positionBase + 2], pixelData[positionBase + 1], pixelData[positionBase], pixelData[positionBase + 3]};
	else
		return {pixelData[positionBase + 2], pixelData[positionBase + 1], pixelData[positionBase]};
}
void ImageBMP::setPixel(int x, int y, Pixel newPixel)
{
	positionBase = CHANNELS * (y * bmp_info_header.width + x);
	pixelData[positionBase + 2] = newPixel.red;
	pixelData[positionBase + 1] = newPixel.green;
	pixelData[positionBase] = newPixel.blue; // + 0
	if (CHANNELS == 4)
		pixelData[positionBase + 3] = newPixel.alpha;
}
uint8_t ImageBMP::getRed(int x, int y)
{
	return pixelData[CHANNELS * (y * bmp_info_header.width + x) + 2]; //static_cast<int>(pixelData[x])
}
uint8_t ImageBMP::getGreen(int x, int y)
{
	return pixelData[CHANNELS * (y * bmp_info_header.width + x) + 1];
}
uint8_t ImageBMP::getBlue(int x, int y)
{
	return pixelData[CHANNELS * (y * bmp_info_header.width + x)];
}

uint8_t ImageBMP::getAplha(int x, int y)
{
	if (CHANNELS == 4)
		return pixelData[CHANNELS * (y * bmp_info_header.width + x) + 3];
	else
		return 255;
}
bool ImageBMP::saveImage()
{
	std::ofstream outf(filepath, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outf.is_open())
	{
		return false;
	}
	outf.write(reinterpret_cast<char*>(&headerBMP), sizeof(BMPFileHeader));
	outf.write(reinterpret_cast<char*>(&bmp_info_header), sizeof(BMPInfoHeader));
	outf.write(reinterpret_cast<char*>(&bmp_color_header), sizeof(BMPColorHeader));
	outf.write(reinterpret_cast<char*>(pixelData.data()), pixelData.size());
	return true;
}
Image::ImageInfo ImageBMP::getImageInfo() const
{
	return imageInfo;
}
ImageBMP::~ImageBMP()
{
	std::cout << "Image: " << filename << " destructed successfully" << std::endl;
}
}
