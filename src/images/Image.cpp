//==============================================================================
// File       : Image.cpp
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Feb 24, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Image.h"

namespace Images
{
Image::Image(std::string filepath) : filepath(filepath), fileStatus("Pending"), fileState(FileState::ERROR), inverted(false), pixelFormat(PixelFormat::RGB), imageData(nullptr), CHANNELS(3)
{
	size_t xPos;
	if ((xPos = filepath.find_last_of('/')) != std::string::npos)
		this->filename = filepath.substr(xPos + 1);
	else
		this->filename = filepath;

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
PixelFormat Image::getPixelFormat()
{
	return pixelFormat;
}
unsigned char* Image::getImageData() const
{
	if (imageData)
		return imageData;
	unsigned char* imageDat = new unsigned char[imageInfo.width * imageInfo.height * 4];
	Pixel pixel;
	int xyCord = 0;
	for(int y = 0; y < imageInfo.height; y++)
	{
		for (int x = 0; x < imageInfo.width; x++)
		{
			pixel = getPixel(x, y);
			xyCord = y * imageInfo.width + x;
			imageDat[xyCord] = pixel.red;
			imageDat[xyCord + 1] = pixel.green;
			imageDat[xyCord + 2] = pixel.blue;
			imageDat[xyCord + 2] = pixel.alpha;
		}
	}
	return imageDat;
}
} /* namespace Images */
