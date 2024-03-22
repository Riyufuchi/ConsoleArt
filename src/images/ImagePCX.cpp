//==============================================================================
// File       : ImagePCX.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Mar 22, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImagePCX.h"

namespace Images
{
ImagePCX::ImagePCX(std::string filename) : Image(filename)
{
	loadImage();
}
ImagePCX::~ImagePCX()
{
}
void ImagePCX::loadImage()
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
	imageInfo.name = filename;
	imageInfo.width = (headerPCX.xMax - headerPCX.xMin) + 1;;
	imageInfo.height = (headerPCX.yMax - headerPCX.yMin) + 1;
	imageInfo.file_type = headerPCX.file_type;
	imageInfo.bits = headerPCX.numOfColorPlanes * 8;

	readImageData(inf);
	/*switch (headerPCX.numOfColorPlanes)
	{
		case 3: make24bitPCX(); break;
		case 4: make32bitPCX(); break;
		default: this->fileStatus = "Unexpected number of color planes"; return;
	}*/

	this->fileStatus = "OK";
}
void ImagePCX::readImageData(std::ifstream& inf)
{
	int width = imageInfo.width;
	int height = imageInfo.height;
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
			}
			index += restOfBits;
		}
	}
}
/*void ImagePCX::make24bitPCX()
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
}*/
void ImagePCX::updateImage()
{
	const int INDEX_BASE = 3 * imageInfo.width;
	const int PLANE_GREEN = imageInfo.width;
	const int PLANE_BLUE = 2 * imageInfo.width;
	const int PLANE_ALPHA = 3 * imageInfo.width;
	int index = 0;
	Pixel newPixel;
	for (int y = 0; y < imageInfo.height; y++)
	{
		for (int x = 0; x < imageInfo.width; x++)
		{
			index = (y * INDEX_BASE + x);
			newPixel = getPixel(x, y);
			imageData[index] = newPixel.red;
			imageData[index + PLANE_GREEN]= newPixel.green;
			imageData[index + PLANE_BLUE] = newPixel.blue;
			if (headerPCX.numOfColorPlanes == 4)
				imageData[index + PLANE_ALPHA] = newPixel.alpha;
		}
	}
}
void ImagePCX::checkHeader()
{
	if (headerPCX.file_type != 0x0A)
		throw std::runtime_error("Unrecognized format " + getFilename().substr(getFilename().find_last_of(".")));
	if (!(headerPCX.numOfColorPlanes == 3) && (headerPCX.bitsPerPixel == 8))
		throw std::runtime_error("This reader works only with 24-bit and 32-bit true color images");
	if (headerPCX.encoding == 0)
		throw std::runtime_error("Uncompressed image");
	if (headerPCX.version != 5)
		throw std::runtime_error("Outdated versions are not supported");
}
Image::ImageInfo ImagePCX::getImageInfo() const
{
	return imageInfo;
}
Image::Pixel ImagePCX::getPixel(int x, int y)
{
	positionBase = y * 3 *imageInfo.width + x;
	if (headerPCX.numOfColorPlanes == 4)
		return Pixel{imageData[positionBase], imageData[positionBase + imageInfo.width], imageData[positionBase + 2 * imageInfo.width], imageData[positionBase + 3 * imageInfo.width]};
	return Pixel{imageData[positionBase], imageData[positionBase + imageInfo.width], imageData[positionBase + 2 * imageInfo.width], 255};
}
void ImagePCX::setPixel(int x, int y, Pixel newPixel)
{
	//pixels[y * info.width + x] = newPixel;
	int index = y * 3 * imageInfo.width + x;
	imageData[index] = newPixel.red;
	imageData[index + imageInfo.width]= newPixel.green;
	imageData[index + 2 * imageInfo.width] = newPixel.blue;
	if (headerPCX.numOfColorPlanes == 4)
		imageData[index + 3 * imageInfo.width] = newPixel.alpha;
}
const bool ImagePCX::saveImage()
{
	std::ofstream outf(filepath, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outf.is_open())
	{
		return false;
	}
	outf.write(reinterpret_cast<char*>(&headerPCX), sizeof(PCXHeader));
	switch (headerPCX.numOfColorPlanes)
	{
		case 3: write24and32bitPCX(outf); break;
		case 4: write24and32bitPCX(outf); break;
		default:
			this->fileStatus = "Unexpected number of color planes";
			outf.close();
			return false;
	}
	outf.close();
	return true;
}
void ImagePCX::write24and32bitPCX(std::ofstream& outf)
{
	uint8_t byte = 0;
	size_t index = 0;
	uint8_t numByte = 0;
	uint8_t lastByte = 0;
	while (index < imageData.size())
	{
		byte = imageData[index];
		if (byte >> 6 != 3)
		{
			outf.write(reinterpret_cast<char*>(&byte), sizeof(byte));
			index++;
		}
		else
		{
			lastByte = byte;
			while (imageData[index] == lastByte && numByte < 63)
			{
				index++;
				numByte++;
			}
			numByte |= 0xC0;
			outf.write(reinterpret_cast<char*>(&numByte), sizeof(byte));
			outf.write(reinterpret_cast<char*>(&lastByte), sizeof(byte));
			numByte = 0;
		}
	}
}
} /* namespace Images */
