//==============================================================================
// File       : Image.cpp
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Mar 2, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Image.h"

namespace Images
{
Image::Image(std::string filepath) : filepath(filepath), fileStatus("Pending"), fileState(FileState::ERROR), inverted(false), pixelByteOrder(PixelByteOrder::RGBA), imageData(nullptr), CHANNELS(3)
{
	size_t xPos;
	if ((xPos = filepath.find_last_of('/')) != std::string::npos)
		this->filename = filepath.substr(xPos + 1);
	else
		this->filename = filepath;

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
unsigned char* Image::getImageData() const
{
	if (imageData)
		return imageData;
	if (!inverted)
		return (unsigned char*)pixelData.data();
	int cp = 4;
	if (CHANNELS <= 3)
		cp = 3;
	unsigned char* imageDat = (unsigned char*)pixelData.data();
	unsigned char* flippedData = new unsigned char[imageInfo.width * imageInfo.height * cp];
	int rowSize = imageInfo.width * cp;
	int srcRow = 0;
	int dstRow = 0;
	for (int y = 0; y < imageInfo.height; y++)
	{
		srcRow = (imageInfo.height - 1 - y) * rowSize;
		dstRow = y * rowSize;
		std::memcpy(&flippedData[dstRow], &imageDat[srcRow], rowSize);
	}
	return flippedData;
}
} /* namespace Images */
