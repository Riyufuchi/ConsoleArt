//==============================================================================
// File       : Image.h
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Feb 13, 2025
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
class Image
{
public:
	struct ImageInfo
	{
		std::string name {"Unknown"};
		int width {0};
		int height {0};
		//int sizeInBytes;
		uint16_t bits {24};
		uint16_t file_type {0};
	};
protected:
	std::string filepath;
	std::string fileStatus;
	std::string filename;
	FileState fileState;
	bool inverted;
	ImageInfo imageInfo;
	std::vector<uint8_t> pixelData; //Or unsigned char can be used
	int positionBase;
public:
	Image(std::string filepath);
	virtual ~Image() = default;
	explicit operator bool() const
	{
		return fileState == FileState::OK;
	}

	/*explicit operator std::string() const
	{
		return filename;
	}*/

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
	// Common
	void rename(std::string imageName);
	// Utils
	virtual bool saveImage() = 0;
	virtual void loadImage() = 0;
	//virtual void resize(int width, int heigh) = 0;
	// Is methods
	bool isLoaded() const;
	bool isInverted() const;
	// Getters
	virtual const std::string& getFilename() const final;
	virtual const std::string& getFilepath() const final;
	virtual const std::string& getFileStatus() const final;
	virtual ImageInfo getImageInfo() const = 0;
	virtual Pixel getPixel(int x, int y) = 0;
	//Setters
	virtual void setPixel(int x, int y, Pixel newPixel) = 0;
};
} /* namespace Images */
#endif /* IMAGES_IMAGE_H_ */
