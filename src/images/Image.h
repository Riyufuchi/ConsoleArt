//==============================================================================
// File       : Image.h
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Nov 07, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: Abstract class for specific image formats
//==============================================================================

#ifndef _IMAGES_IMAGE_H_
#define _IMAGES_IMAGE_H_

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <cstring>
#include <memory>

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
	std::string name {"unknown.txt"};
	int width {0};
	int height {0};
	uint16_t bits {24};
	uint16_t file_type {0};
	bool planar {false};
	bool palette {false};
	bool animated {false};
	bool multipage {false};
};
struct TechnicalInfo
{
	std::string technicalMessage { "Pending/unknown" };
	bool inverted { false };
	int channels { 3 };
	PixelByteOrder pixelByteOrder { PixelByteOrder::RGBA };
	FileState fileState { FileState::ERROR };
};
class Image
{
protected:
	std::string filepath;
	ImageInfo image;
	TechnicalInfo technical;
	std::vector<uint8_t> pixelData;
public:
	Image(std::string filepath);
	Image(Image&) = delete;
	Image(Image&&) = delete;

	virtual ~Image();

	Image& operator=(Image&) = delete;
	Image& operator=(Image&&) = delete;

	explicit operator bool() const
	{
		return technical.fileState == FileState::OK;
	}

	explicit operator std::string() const
	{
		return image.name;
	}

	friend std::ostream& operator<<(std::ostream& os, const Image& img);

	bool operator > (const Image& other) const
	{
		return image.width * image.height > other.image.width * other.image.height;
	}

	bool operator < (const Image& other) const
	{
		return image.width * image.height < other.image.width * other.image.height;
	}

	bool operator == (const Image& other) const
	{
		return image.width * image.height == other.image.width * other.image.height;
	}

	bool operator != (const Image& other) const
	{
		return image.width * image.height != other.image.width * other.image.height;
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
	std::unique_ptr<unsigned char[]> getImageData() const;
	//Setters
	virtual void setPixel(int x, int y, Pixel newPixel) = 0;
};
} /* namespace Images */
#endif /* IMAGES_IMAGE_H_ */
