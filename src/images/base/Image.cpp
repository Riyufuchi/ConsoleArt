//==============================================================================
// File       : Image.cpp
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Nov 20, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consoleart
//==============================================================================

#include "Image.h"

namespace consoleartlib
{
Image::Image(std::string filepath, ImageType format) : filepath(filepath)
{
	size_t xPos;
	if ((xPos = filepath.find_last_of('/')) != std::string::npos)
		this->image.name = filepath.substr(xPos + 1);
	else
		this->image.name = filepath;
	image.imageFormat = format;
}
Image::~Image()
{
}
std::ostream& operator<<(std::ostream& os, const Image& img)
{
	return os << std::boolalpha << "Name: " << img.image.name << "\n"
			<< "Width: " << img.image.width << " px\n"
			<< "Height: " << img.image.height << " px\n"
			<< "Bits: " << img.image.bits << "\n"
			<< "Inverted: " << img.image.inverted << "\n"
			<< "Planar: " << img.image.planar << "\n"
			<< "Palate: " << img.image.palette << "\n"
			<< "Animated: " << img.image.animated << "\n"
			<< "Multi-page: " << img.image.multipage << "\n"
			<< "HDR: " << img.image.hdr << "\n" << std::noboolalpha;
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
bool Image::containsPalette() const
{
	return image.palette;
}
bool Image::isLoaded() const
{
	return technical.fileState == FileState::OK;
}
bool Image::isInverted() const
{
	return image.inverted;
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
	return image.pixelByteOrder;
}
std::unique_ptr<unsigned char[]> Image::getImageData() const
{
	if (!image.inverted)
	{
		std::unique_ptr<unsigned char[]> dataCopy = std::make_unique<unsigned char[]>(pixelData.size());
		std::memcpy(dataCopy.get(), pixelData.data(), pixelData.size());
		return dataCopy; // Returning a copy of pixelData, since caller will own it
	}

	int cp = (image.channels <= 3) ? 3 : 4;
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

} /* namespace consoleartlib */
