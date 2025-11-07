//==============================================================================
// File       : Image.cpp
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Nov 07, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Image.h"

namespace Images
{
Image::Image(std::string filepath) : filepath(filepath)
{
	size_t xPos;
	if ((xPos = filepath.find_last_of('/')) != std::string::npos)
		this->image.name = filepath.substr(xPos + 1);
	else
		this->image.name = filepath;
}
Image::~Image()
{
}
std::ostream& operator<<(std::ostream& os, const Image& img)
{
	return os << "Image Name: " << img.image.name << "\n"
			<< "Width: " << img.image.width << " px\n"
			<< "Height: " << img.image.height << " px\n"
			<< "Bits: " << img.image.bits << "\n"
			<< "Inverted: " << (img.technical.inverted ? "Yes" : "No") << "\n"
			<< "Planar: " << (img.image.planar ? "Yes" : "No") << "\n"
			<< "Animated: " << (img.image.animated ? "Yes" : "No") << "\n"
			<< "Multi-page: " << (img.image.multipage ? "Yes" : "No") << "\n"
			<< "HDR: " << (img.image.hdr ? "Yes" : "No") << "\n";
}
void Image::rename(std::string imageName)
{
	imageName = imageName.append(image.name.substr(image.name.find('.')));
	filepath = filepath.substr(0, (filepath.length() - image.name.length())).append(imageName);
	image.name = imageName;
}
const ImageInfo& Image::getImageInfo() const
{
	return image;
}
const std::string& Image::getFileStatus() const
{
	return technical.technicalMessage;
}
const std::string& Image::getFilename() const
{
	return image.name;
}
const std::string& Image::getFilepath() const
{
	return filepath;
}
bool Image::isLoaded() const
{
	return technical.fileState == OK;
}
bool Image::isInverted() const
{
	return technical.inverted;
}
int Image::getWidth() const
{
	return image.width;
}
int Image::getHeight() const
{
	return image.height;
}
int Image::getBits() const
{
	return image.bits;
}
PixelByteOrder Image::getPixelFormat() const
{
	return technical.pixelByteOrder;
}
std::unique_ptr<unsigned char[]> Image::getImageData() const
{
	if (!technical.inverted)
	{
		std::unique_ptr<unsigned char[]> dataCopy = std::make_unique<unsigned char[]>(pixelData.size());
		std::memcpy(dataCopy.get(), pixelData.data(), pixelData.size());
		return dataCopy; // Returning a copy of pixelData, since caller will own it
	}

	int cp = (technical.channels <= 3) ? 3 : 4;
	std::unique_ptr<unsigned char[]> flippedData = std::make_unique<unsigned char[]>(image.width * image.height * cp);

	int rowSize = image.width * cp;
	int srcRow = 0, dstRow = 0;
	for (int y = 0; y < image.height; y++)
	{
		srcRow = (image.height - 1 - y) * rowSize;
		dstRow = y * rowSize;
		std::memcpy(&flippedData[dstRow], &pixelData[srcRow], rowSize);
	}

	return flippedData;
}

} /* namespace Images */
