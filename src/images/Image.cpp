//==============================================================================
// File       : Image.cpp
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Image.h"
#include "Pixels.hpp"

namespace Images
{
Image::Image(std::string filepath) : filepath(filepath), fileStatus("Pending"), fileState(FileState::ERROR), inverted(false), pixelByteOrder(PixelByteOrder::RGBA), imageData(nullptr), CHANNELS(3)
{
	size_t xPos;
	if ((xPos = filepath.find_last_of('/')) != std::string::npos)
		this->filename = filepath.substr(xPos + 1);
	else
		this->filename = filepath;
	imageInfo.name = filename;

}
Image::~Image()
{
}
void Image::rename(std::string imageName)
{
	imageName = imageName.append(filename.substr(filename.find('.')));
	filepath = filepath.substr(0, (filepath.length() - filename.length())).append(imageName);
	filename = imageName;
	imageInfo.name = imageName;
}
const ImageInfo& Image::getImageInfo() const
{
	return imageInfo;
}
const std::string& Image::getFileStatus() const
{
	return fileStatus;
}
const std::string& Image::getFilename() const
{
	return filename;
}
const std::string& Image::getFilepath() const
{
	return filepath;
}
bool Image::isLoaded() const
{
	return fileState == OK;
}
bool Image::isInverted() const
{
	return inverted;
}
int Image::getWidth() const
{
	return imageInfo.width;
}
int Image::getHeight() const
{
	return imageInfo.height;
}
int Image::getBits() const
{
	return imageInfo.bits;
}
PixelByteOrder Image::getPixelFormat() const
{
	return pixelByteOrder;
}
std::unique_ptr<unsigned char[]> Image::getImageData() const
{
	if (imageData)
	{
		std::unique_ptr<unsigned char[]> dataCopy = std::make_unique<unsigned char[]>(imageInfo.width * imageInfo.height * CHANNELS);
		std::memcpy(dataCopy.get(), imageData, imageInfo.width * imageInfo.height * CHANNELS);
		return dataCopy; // Copy existing data
	}
	
	if (!inverted)
	{
		std::unique_ptr<unsigned char[]> dataCopy = std::make_unique<unsigned char[]>(pixelData.size());
		std::memcpy(dataCopy.get(), pixelData.data(), pixelData.size());
		return dataCopy; // Returning a copy of pixelData, since caller will own it
	}

	int cp = (CHANNELS <= 3) ? 3 : 4;
	std::unique_ptr<unsigned char[]> flippedData = std::make_unique<unsigned char[]>(imageInfo.width * imageInfo.height * cp);

	int rowSize = imageInfo.width * cp;
	int srcRow = 0, dstRow = 0;
	for (int y = 0; y < imageInfo.height; y++)
	{
		srcRow = (imageInfo.height - 1 - y) * rowSize;
		dstRow = y * rowSize;
		std::memcpy(&flippedData[dstRow], &pixelData[srcRow], rowSize);
	}

	return flippedData;
}

} /* namespace Images */
