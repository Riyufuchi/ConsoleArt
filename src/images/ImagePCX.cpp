//==============================================================================
// File       : ImagePCX.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : May 13, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImagePCX.h"

namespace Images
{
ImagePCX::ImagePCX(std::string filename) : Image(filename)
{
	this->paletteVGA = NULL;
	this->image.planar = true;
	loadImage();
	this->BLUE_OFFSET = 2 * headerPCX.bytesPerLine;
	this->ALPHA_OFFSET = 3 * headerPCX.bytesPerLine;
	if (headerPCX.numOfColorPlanes == 4)
	{
		image.bits = 32;
	}
}
ImagePCX::~ImagePCX()
{
	if (paletteVGA != nullptr)
	{
		delete[] paletteVGA;
		paletteVGA = nullptr;
	}
}
void ImagePCX::loadImage()
{
	std::ifstream inf(filepath, std::ios::in | std::ios::binary);
	if (!inf)
	{
		this->technical.technicalMessage = "Unable to open file: " + image.name;
		return;
	}
	inf.read(reinterpret_cast<char*>(&headerPCX), sizeof(headerPCX));
	image.width = (headerPCX.xMax - headerPCX.xMin) + 1;;
	image.height = (headerPCX.yMax - headerPCX.yMin) + 1;
	image.file_type = headerPCX.file_type;
	image.bits = headerPCX.numOfColorPlanes * 8;
	try
	{
		checkHeader();
	}
	catch (std::runtime_error& e)
	{
		this->technical.technicalMessage = e.what();
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
				this->technical.technicalMessage = "Uncompressed image data are not supported for 24 and 32 bit images";
				success = false;
			}
			decodeRLE(inf, pixelData);
		break;
		default: this->technical.technicalMessage = "Unexpected number of color planes"; return;
	}
	if (success)
	{
		this->technical.technicalMessage = "OK";
		this->technical.fileState = FileState::OK;
	}
}
void ImagePCX::decodeRLE(std::ifstream& inf, std::vector<uint8_t>& imageData)
{
	int height = image.height;
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
	image.palette = true;
	image.planar = false;
	// Read palete
	if (!readPaletteVGA(stream))
	{
		this->technical.technicalMessage = "Error during palette loading";
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
		imageData.resize((image.width * image.height));
		stream.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
	}
	pixelData.resize(image.width * image.height * 3);
	int x = 0;
	PixelRGB pRGB;
	int i = 0;
	for (int y = 0; y < image.height; y++)
	{
		for (x = 0; x < image.width; x++)
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
const ImagePCX::PCXHeader& ImagePCX::getHeader() const
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
void ImagePCX::checkHeader()
{
	if (headerPCX.file_type != 0x0A)
		throw std::runtime_error("Unrecognized format " + image.name.substr(image.name.find_last_of(".")));
	if ((!(headerPCX.numOfColorPlanes == 3) && (headerPCX.bitsPerPixel == 8)) &&
			(!havePalette())) // 24 and 32 bit images && VGA palette
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
