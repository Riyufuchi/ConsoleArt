//==============================================================================
// File       : ImagePCX.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Nov 15, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImagePCX.h"

namespace Images
{
ImagePCX::ImagePCX(std::string filename) : Image(filename, ImageType::PCX)
{
	this->paletteVGA = nullptr;
	this->image.planar = true;
	loadImage();
	this->BLUE_OFFSET = 2 * headerPCX.bytesPerLine;
	this->ALPHA_OFFSET = 3 * headerPCX.bytesPerLine;
}

ImagePCX::~ImagePCX()
{
	if (paletteVGA)
	{
		delete[] paletteVGA;
		paletteVGA = nullptr;
	}
}
PixelRGB* ImagePCX::readPaletteVGA(std::ifstream& stream, const uint32_t end)
{
	char VGAPaletteMarker;
	stream.seekg(end - 769);
	stream.read(&VGAPaletteMarker, 1);
	if (VGAPaletteMarker != 0x0c || stream.fail())
		return 0;
	PixelRGB* paletteVGA = new PixelRGB[256];
	for (int entry = 0; entry < 256; entry++)
		stream.read(reinterpret_cast<char*>(&paletteVGA[entry]), 3);
	if (stream.fail() && paletteVGA)
	{
		delete[] paletteVGA;
		paletteVGA = nullptr;
	}
	return paletteVGA;
}

uint32_t ImagePCX::calcFileEnd(std::ifstream& stream)
{
	// Save current read position
	std::streampos current = stream.tellg();
	// Move to end
	stream.seekg(0, std::ios::end);
	uint32_t end = static_cast<uint32_t>(stream.tellg());
	// Restore position
	stream.seekg(current);
	return end;
}

void ImagePCX::readHeader(std::ifstream& stream, PCXHeader& headerPCX, ImageInfo& image)
{
	stream.read(reinterpret_cast<char*>(&headerPCX), sizeof(headerPCX));
	image.width = (headerPCX.xMax - headerPCX.xMin) + 1;;
	image.height = (headerPCX.yMax - headerPCX.yMin) + 1;
	image.file_type = headerPCX.file_type;
	image.bits = headerPCX.numOfColorPlanes * 8;
	if (headerPCX.numOfColorPlanes == 4)
	{
		image.bits = 32;
	}
}
bool ImagePCX::loadImageDataVGA(std::ifstream& stream, std::vector<uint8_t>& imageData, PCXHeader& headerPCX, ImageInfo& image, std::string& errMsg, PixelRGB*& paletteVGA, const uint32_t start)
{
	if (!isVGA(headerPCX))
		return false;
	paletteVGA = readPaletteVGA(stream, calcFileEnd(stream));
	if (!paletteVGA)
	{
		errMsg = "Error during palete loading";
		return false;
	}
	stream.seekg(start + sizeof(PCXHeader)); // Move back to start of image data
	headerPCX.numOfColorPlanes = 3;
	if (headerPCX.encoding == 1)
	{
		decodeRLE(stream, imageData, headerPCX);
	}
	else
	{
		imageData.resize((image.width * image.height));
		stream.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
	}
	return true;
}
bool ImagePCX::convertImageDataVGA(const std::vector<uint8_t>& imageData, std::vector<uint8_t>& pixelData, const ImageInfo& image, const PixelRGB* paletteVGA)
{
	pixelData.resize(image.width * image.height * 3);
	int i = 0;
	int x, index;
	PixelRGB pRGB;
	for (int y = 0; y < image.height; y++)
	{
		for (x = 0; x < image.width; x++)
		{
			pRGB = paletteVGA[imageData[i]];
			index = y * 3 * image.width + x;
			pixelData[index] = pRGB.red;
			pixelData[index + image.width]= pRGB.green;
			pixelData[index + 2 * image.width] = pRGB.blue;
			i++;
		}
	}
	return true;
}
void ImagePCX::loadImage()
{
	std::ifstream stream(filepath, std::ios::in | std::ios::binary);
	if (!stream)
	{
		this->technical.technicalMessage = "Unable to open file: " + image.name;
		return;
	}
	readHeader(stream, headerPCX, image);
	try
	{
		checkHeader(headerPCX, image);
	}
	catch (std::runtime_error& e)
	{
		this->technical.technicalMessage = e.what();
		return;
	}
	bool success = true;
	std::vector<uint8_t> imageData;
	switch (headerPCX.numOfColorPlanes)
	{
		case 1:
			image.palette = true;
			image.planar = false;
			if (loadImageDataVGA(stream, imageData, headerPCX, image, technical.technicalMessage, paletteVGA, 0))
				success = convertImageDataVGA(imageData, pixelData, image, paletteVGA);
			else
				success = false;
		 break;
		case 3:
		case 4:
			if (headerPCX.encoding == 0)
			{
				this->technical.technicalMessage = "Uncompressed image data are not supported for 24 and 32 bit images";
				success = false;
			}
			decodeRLE(stream, pixelData, headerPCX);
		break;
		default: this->technical.technicalMessage = "Unexpected number of color planes"; return;
	}
	if (success)
	{
		this->technical.fileState = FileState::OK;
	}
}
void ImagePCX::decodeRLE(std::ifstream& inf, std::vector<uint8_t>& imageData, const PCXHeader& headerPCX)
{
	int height = (headerPCX.yMax - headerPCX.yMin) + 1;
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
bool ImagePCX::containsPalette() const
{
	return image.palette;
}
bool ImagePCX::isVGA(const PCXHeader& headerPCX)
{
	return headerPCX.version == 5 && headerPCX.numOfColorPlanes == 1 && headerPCX.bitsPerPixel > 4;
}
const ImagePCX::PCXHeader& ImagePCX::getHeader() const
{
	return headerPCX;
}
void ImagePCX::updateImage()
{
	const int INDEX_BASE = headerPCX.bytesPerLine * headerPCX.numOfColorPlanes;
	const int PLANE_GREEN = headerPCX.bytesPerLine;
	const int PLANE_BLUE = BLUE_OFFSET;
	const int PLANE_ALPHA = ALPHA_OFFSET;
	int index = 0;
	Pixel newPixel;
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
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
void ImagePCX::checkHeader(const PCXHeader& headerPCX, const ImageInfo& image)
{
	if (headerPCX.file_type != 0x0A)
		throw std::runtime_error("Unrecognized format " + image.name.substr(image.name.find_last_of(".")));
	if ((!(headerPCX.numOfColorPlanes == 3) && (headerPCX.bitsPerPixel == 8)) &&
			(!isVGA(headerPCX))) // 24 and 32 bit images && VGA palette
		throw std::runtime_error("This reader works only with 24-bit and 32-bit true color and VGA images");
	if (headerPCX.version != 5)
		throw std::runtime_error("Outdated versions are not supported");
}
Pixel ImagePCX::getPixel(int x, int y) const
{
	x = (y * headerPCX.bytesPerLine * headerPCX.numOfColorPlanes) + x;
	if (headerPCX.numOfColorPlanes == 4)
		return {pixelData[x], pixelData[x + headerPCX.bytesPerLine], pixelData[x + BLUE_OFFSET], pixelData[x + ALPHA_OFFSET]};
	return {pixelData[x], pixelData[x + headerPCX.bytesPerLine], pixelData[x + BLUE_OFFSET], 255};
}
void ImagePCX::setPixel(int x, int y, Pixel newPixel)
{
	//pixels[y * info.width + x] = newPixel;
	x = y * 3 * image.width + x;
	pixelData[x] = newPixel.red;
	pixelData[x + image.width]= newPixel.green;
	pixelData[x + 2 * image.width] = newPixel.blue;
	if (headerPCX.numOfColorPlanes == 4)
		pixelData[x + 3 * image.width] = newPixel.alpha;
}
bool ImagePCX::saveImage(std::ofstream& stream) const
{
	if (!stream.is_open())
	{
		return false;
	}
	stream.write(reinterpret_cast<const char*>(&headerPCX), sizeof(PCXHeader));
	switch (headerPCX.numOfColorPlanes)
	{
		case 3:
		case 4: write24and32bitPCX(stream); break;
		default: return false;
	}
	return true;
}
bool ImagePCX::saveImage() const
{
	std::ofstream outf(filepath, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outf.is_open())
	{
		return false;
	}
	outf.write(reinterpret_cast<const char*>(&headerPCX), sizeof(PCXHeader));
	switch (headerPCX.numOfColorPlanes)
	{
		case 3: write24and32bitPCX(outf); break;
		case 4: write24and32bitPCX(outf); break;
		default:
			//this->fileStatus = "Unexpected number of color planes";
			outf.close();
			return false;
	}
	outf.close();
	return true;
}
void ImagePCX::write24and32bitPCX(std::ofstream& outf) const
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
			outf.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
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
			outf.write(reinterpret_cast<const char*>(&numByte), sizeof(byte));
			outf.write(reinterpret_cast<const char*>(&lastByte), sizeof(byte));
			numByte = 0;
		}
	}
}
} /* namespace Images */
