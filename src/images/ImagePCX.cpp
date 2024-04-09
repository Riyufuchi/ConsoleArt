//==============================================================================
// File       : ImagePCX.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Apr 09, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImagePCX.h"

namespace Images
{
ImagePCX::ImagePCX(std::string filename) : Image(filename)
{
	this->paletteVGA = NULL;
	loadImage();
	this->BLUE_OFFSET = 2 * headerPCX.bytesPerLine;
	this->ALPHA_OFFSET = 3 * headerPCX.bytesPerLine;
}
ImagePCX::~ImagePCX()
{
	if(paletteVGA != NULL)
	{
		delete[] paletteVGA;
		paletteVGA = NULL;
	}
}
void ImagePCX::loadImage()
{
	std::ifstream inf(filepath, std::ios::in | std::ios::binary);
	if (!inf)
	{
		this->fileStatus = "Unable to open file: " + filename;
		return;
	}
	inf.read(reinterpret_cast<char*>(&headerPCX), sizeof(headerPCX));
	imageInfo.name = filename;
	imageInfo.width = (headerPCX.xMax - headerPCX.xMin) + 1;;
	imageInfo.height = (headerPCX.yMax - headerPCX.yMin) + 1;
	imageInfo.file_type = headerPCX.file_type;
	imageInfo.bits = headerPCX.numOfColorPlanes * 8;
	try
	{
		checkHeader();
	}
	catch (std::runtime_error& e)
	{
		this->fileStatus = e.what();
		return;
	}
	bool success = true;
	switch (headerPCX.numOfColorPlanes)
	{
		case 1: success = readImageData(inf); break;
		case 3:
		case 4:
			if (headerPCX.encoding == 0)
			{
				this->fileStatus = "Uncompressed image data are not supported for 24 and 32 bit images";
				success = false;
			}
			decodeRLE(inf, pixelData);
			break;
		default: this->fileStatus = "Unexpected number of color planes"; return;
	}

	if (success)
		this->fileStatus = "OK";
}
void ImagePCX::decodeRLE(std::ifstream& inf, std::vector<uint8_t>& imageData)
{
	int height = imageInfo.height;
	const long dataSize = headerPCX.bytesPerLine * headerPCX.bitsPerPixel * height;
	// Initialize vector
	imageData.clear();
	imageData.reserve(dataSize);
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
bool ImagePCX::readImageData(std::ifstream& stream)
{
	// Read palete
	if (!readPaletteVGA(stream))
	{
		this->fileStatus = "Error during palette loading";
		return false;
	}
	// Read image data
	stream.seekg(sizeof(PCXHeader)); // Move back to start of image data
	headerPCX.numOfColorPlanes = 3;
	std::vector<uint8_t> imageData;
	if (headerPCX.encoding == 1)
	{
		decodeRLE(stream, imageData);
	}
	else
	{
		imageData.reserve((imageInfo.width * imageInfo.height));
		stream.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
	}
	pixelData.reserve(imageData.size() * 6);
	int x = 0;
	PixelRGB pRGB;
	int i = 0;
	for (int y = 0; y < imageInfo.height; y++)
	{
		for (x = 0; x < imageInfo.width; x++)
		{
			pRGB = paletteVGA[imageData[i]];
			setPixel(x, y, Pixel{pRGB.red, pRGB.green, pRGB.blue});
			i++;
		}
	}
	return true;
}
bool ImagePCX::readPaletteVGA(std::ifstream& stream)
{
	if (!havePalette())
		return false;
	char VGAPaletteMarker;
	stream.seekg(-769, std::ios_base::end);
	stream.read(&VGAPaletteMarker, 1);
	if (VGAPaletteMarker != 0x0c || stream.fail())
		return false;
	paletteVGA = new PixelRGB[256];
	for (int entry = 0; entry < 256; entry++)
		stream.read(reinterpret_cast<char*>(&paletteVGA[entry]), 3);
	return !stream.fail();
}
bool ImagePCX::havePalette() const
{
	return headerPCX.version == 5 && headerPCX.numOfColorPlanes == 1 && headerPCX.bitsPerPixel > 4;
}
ImagePCX::PCXHeader& ImagePCX::getHeader()
{
	return headerPCX;
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
	const int INDEX_BASE = headerPCX.bytesPerLine * headerPCX.numOfColorPlanes;
	const int PLANE_GREEN = headerPCX.bytesPerLine;
	const int PLANE_BLUE = BLUE_OFFSET;
	const int PLANE_ALPHA = ALPHA_OFFSET;
	int index = 0;
	Pixel newPixel;
	for (int y = 0; y < imageInfo.height; y++)
	{
		for (int x = 0; x < imageInfo.width; x++)
		{
			index = (y * INDEX_BASE + x);
			newPixel = getPixel(x, y);
			pixelData[index] = newPixel.red;
			pixelData[index + PLANE_GREEN]= newPixel.green;
			pixelData[index + PLANE_BLUE] = newPixel.blue;
			if (headerPCX.numOfColorPlanes == 4)
				pixelData[index + PLANE_ALPHA] = newPixel.alpha;
		}
	}
}
void ImagePCX::checkHeader()
{
	if (headerPCX.file_type != 0x0A)
		throw std::runtime_error("Unrecognized format " + filename.substr(filename.find_last_of(".")));
	if ((!(headerPCX.numOfColorPlanes == 3) && (headerPCX.bitsPerPixel == 8)) &&
			(!havePalette())) // 24 and 32 bit images && VGA palette
		throw std::runtime_error("This reader works only with 24-bit and 32-bit true color and VGA images");
	if (headerPCX.version != 5)
		throw std::runtime_error("Outdated versions are not supported");
}
Image::ImageInfo ImagePCX::getImageInfo() const
{
	return imageInfo;
}
Pixel ImagePCX::getPixel(int x, int y)
{
	positionBase = y * headerPCX.bytesPerLine * headerPCX.numOfColorPlanes + x;
	if (headerPCX.numOfColorPlanes == 4)
		return Pixel{pixelData[positionBase], pixelData[positionBase + headerPCX.bytesPerLine], pixelData[positionBase + BLUE_OFFSET], pixelData[positionBase + ALPHA_OFFSET]};
	return Pixel{pixelData[positionBase], pixelData[positionBase + headerPCX.bytesPerLine], pixelData[positionBase + BLUE_OFFSET], 255};
}
void ImagePCX::setPixel(int x, int y, Pixel newPixel)
{
	//pixels[y * info.width + x] = newPixel;
	int index = y * 3 * imageInfo.width + x;
	pixelData[index] = newPixel.red;
	pixelData[index + imageInfo.width]= newPixel.green;
	pixelData[index + 2 * imageInfo.width] = newPixel.blue;
	if (headerPCX.numOfColorPlanes == 4)
		pixelData[index + 3 * imageInfo.width] = newPixel.alpha;
}
/*void ImagePCX::setPixel(int x, int y, Pixel newPixel)
{
	//pixels[y * info.width + x] = newPixel;
	//int index = y * 3 * imageInfo.width + x;
	positionBase = y * headerPCX.bytesPerLine * headerPCX.numOfColorPlanes + x;
	pixelData[positionBase] = newPixel.red;
	pixelData[positionBase + headerPCX.bytesPerLine]= newPixel.green;
	pixelData[positionBase + BLUE_OFFSET] = newPixel.blue;
	if (headerPCX.numOfColorPlanes == 4)
		pixelData[positionBase + ALPHA_OFFSET] = newPixel.alpha;
}*/
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
	while (index < pixelData.size())
	{
		byte = pixelData[index];
		if (byte >> 6 != 3)
		{
			outf.write(reinterpret_cast<char*>(&byte), sizeof(byte));
			index++;
		}
		else
		{
			lastByte = byte;
			while (pixelData[index] == lastByte && numByte < 63)
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
