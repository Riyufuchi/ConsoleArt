//==============================================================================
// File       : ImagePCX.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : 07.12.2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImagePCX.h"

namespace Images
{
ImagePCX::ImagePCX(std::string filename) : Image(filename)
{
	readPCX();
}
ImagePCX::~ImagePCX()
{
}
void ImagePCX::readPCX()
{
	std::ifstream inf(filepath, std::ios::in | std::ios::binary);
	if (!inf)
	{
		this->fileStatus = "Unable to open file: " + getFilename();
		return;
	}
	inf.read(reinterpret_cast<char*>(&headerPCX), sizeof(headerPCX));
	try
	{
		checkHeader();
	}
	catch (std::runtime_error& e)
	{
		this->fileStatus = e.what();
		return;
	}
	info.name = getFilename();
	info.width = (headerPCX.xMax - headerPCX.xMin) + 1;;
	info.height = (headerPCX.yMax - headerPCX.yMin) + 1;
	info.file_type = headerPCX.file_type;
	info.bits = headerPCX.numOfColorPlanes * 8;

	readImageData(inf);
	switch (headerPCX.numOfColorPlanes)
	{
		case 3: make24bitPCX(); break;
		case 4: make32bitPCX(); break;
		default: this->fileStatus = "Unexpected number of color planes"; return;
	}

	this->fileStatus = "OK";
}
void ImagePCX::readImageData(std::ifstream& inf)
{
	int width = info.width;
	int height = info.height;
	const int dataSize = width * height * headerPCX.numOfColorPlanes;
	// Initialize vectors
	imageData.clear();
	pixels.clear();
	imageData.reserve(dataSize);
	pixels.reserve(width * height);
	// Read RLE-encoded image data
	uint8_t byte = 0;
	int index = 0;
	int restOfBits = 0;
	int i = 0;
	while (index < dataSize && !inf.eof())
	{
		inf.read(reinterpret_cast<char*>(&byte), sizeof(byte));
		if (byte >> 6 != 3)
		{
			imageData.push_back(byte);
			index++;
		}
		else
		{
			restOfBits = byte & 0x3F;
			inf.read(reinterpret_cast<char*>(&byte), sizeof(byte));
			for(i = 0; i < restOfBits; i++)
			{
				imageData.push_back(byte);
				index++;
			}
		}
	}
}
void ImagePCX::make24bitPCX()
{
	int index = 0;
	const int width3x = info.width * 3;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			index = (y * width3x + x);
			pixels.push_back(Pixel{imageData[index], imageData[index + info.width], imageData[index + 2 * info.width]});
		}
	}
}
void ImagePCX::make32bitPCX()
{
	int index = 0;
	const int width3x = info.width * 3;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
			index = (y * width3x + x);
			pixels.push_back(Pixel{imageData[index], imageData[index + info.width], imageData[index + 2 * info.width], imageData[index + width3x]});
		}
	}
}
void ImagePCX::checkHeader()
{
	if (headerPCX.file_type != 0x0A)
		throw std::runtime_error("Unrecognized format " + getFilename().substr(getFilename().find_last_of(".")));
	if (!(headerPCX.numOfColorPlanes == 3) && (headerPCX.bitsPerPixel == 8))
		throw std::runtime_error("This reader works only with 24-bit true color images");
	if (headerPCX.encoding == 0)
		throw std::runtime_error("Uncompressed image");
	if (headerPCX.version != 5)
		throw std::runtime_error("Outdated versions are not supported");
}
Image::ImageInfo ImagePCX::getImageInfo()
{
	return info;
}
Image::Pixel ImagePCX::getPixel(int x, int y)
{
	return pixels[y * info.width + x];
}
void ImagePCX::setPixel(int x, int y, Pixel newPixel)
{
	pixels[y * info.width + x] = newPixel;
}
} /* namespace Images */
