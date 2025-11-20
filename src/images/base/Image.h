//==============================================================================
// File       : Image.h
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Nov 20, 2025
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
#include <algorithm>
#include <cmath>

#include "../utils/Pixels.hpp"

namespace Images
{
enum class ImageType
{
	UNKNOWN,
	BMP,
	PCX,
	PPM,
	PNG,
	JPG,
	GIF,
	HDR,
	TGA,
	DCX
};
enum class FileState
{
	ERROR,
	OK
};
struct ImageInfo
{
	std::string name {"unknown.txt"};
	int width {0};
	int height {0};
	int channels { 3 };
	uint16_t bits { 24 };
	uint16_t file_type { 0 };
	bool planar { false };
	bool palette { false };
	bool animated { false };
	bool multipage { false };
	bool hdr { false };
	bool inverted { false }; // Origin is bottom left when true
	PixelByteOrder pixelByteOrder { PixelByteOrder::RGBA };
	ImageType imageFormat { ImageType::UNKNOWN }; // For casting from base class
};
struct TechnicalInfo
{
	std::string technicalMessage { "Pending/unknown" };
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
	Image(std::string filepath, ImageType format = ImageType::UNKNOWN);
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

	Image& operator>>(const std::string& newName)
	{
		rename(image.name.substr(0, image.name.find(".")) + newName);
		return *this;
	}

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

	auto operator<=>(const Image& other) const
	{
		// compare name first, then width, then height
		return std::tie(image.name, image.width, image.height) <=> std::tie(other.image.name, other.image.width, other.image.height);
	}

	// Utils
	void rename(std::string imageName);
	bool containsPalette() const;
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
