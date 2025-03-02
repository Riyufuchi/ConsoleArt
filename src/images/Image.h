//==============================================================================
// File       : Image.h
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: Abstract class for specific image formats
//==============================================================================

#ifndef _IMAGES_IMAGE_H_
#define _IMAGES_IMAGE_H_

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

#include "Pixels.hpp"

namespace Images
{
enum FileState
{
	ERROR,
	OK
};
struct ImageInfo
{
	std::string name {"Unknown"};
	int width {0};
	int height {0};
	//int sizeInBytes;
	uint16_t bits {24};
	uint16_t file_type {0};
};
class Image
{
protected:
	std::string filepath;
	std::string fileStatus;
	std::string filename;
	FileState fileState;
	bool inverted;
	ImageInfo imageInfo;
	std::vector<uint8_t> pixelData; //Or unsigned char can be used
	PixelByteOrder pixelByteOrder;
	unsigned char* imageData;
	int CHANNELS;
public:
	Image(std::string filepath);
	virtual ~Image();
	explicit operator bool() const
	{
		return fileState == FileState::OK;
	}

	explicit operator std::string() const
	{
		return filename;
	}

	bool operator > (const Image& other) const
	{
		return imageInfo.width * imageInfo.height > other.imageInfo.width * other.imageInfo.height;
	}

	bool operator < (const Image& other) const
	{
		return imageInfo.width * imageInfo.height < other.imageInfo.width * other.imageInfo.height;
	}

	bool operator == (const Image& other) const
	{
		return imageInfo.width * imageInfo.height == other.imageInfo.width * other.imageInfo.height;
	}

	bool operator != (const Image& other) const
	{
		return imageInfo.width * imageInfo.height != other.imageInfo.width * other.imageInfo.height;
	}
	// Utils
	void rename(std::string imageName);
	// Virtual utils
	virtual bool saveImage() const = 0;
	virtual void loadImage() = 0;
	//virtual void resize(int width, int heigh) = 0;
	// Is methods
	bool isLoaded() const;
	bool isInverted() const;
	// Getters
	virtual const std::string& getFilename() const final;
	virtual const std::string& getFilepath() const final;
	virtual const std::string& getFileStatus() const final;
	virtual const ImageInfo& getImageInfo() const final;
	virtual Pixel getPixel(int x, int y) const = 0;
	int getWidth() const;
	int getHeight() const;
	int getBits() const;
	PixelByteOrder getPixelFormat() const;
	unsigned char* getImageData() const;
	//Setters
	virtual void setPixel(int x, int y, Pixel newPixel) = 0;
};
} /* namespace Images */
#endif /* IMAGES_IMAGE_H_ */
