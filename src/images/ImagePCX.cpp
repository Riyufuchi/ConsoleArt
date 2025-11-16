//==============================================================================
// File       : ImagePCX.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Nov 16, 2025
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
bool ImagePCX::readVGA(std::ifstream& stream, PagePCX& pcx, const uint32_t end)
{
	char VGAPaletteMarker;
	stream.seekg(end - 769);
	stream.read(&VGAPaletteMarker, 1);
	if (VGAPaletteMarker != 0x0c || stream.fail())
		return false;
	pcx.palette = new PixelRGB[256];
	for (int entry = 0; entry < 256; entry++)
		stream.read(reinterpret_cast<char*>(&pcx.palette[entry]), 3);
	return !(stream.fail());
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

void ImagePCX::readHeader(std::ifstream& stream, HeaderPCX& headerPCX, ImageInfo& image)
{
	stream.read(reinterpret_cast<char*>(&headerPCX), sizeof(headerPCX));
	image.width = (headerPCX.xMax - headerPCX.xMin) + 1;;
	image.height = (headerPCX.yMax - headerPCX.yMin) + 1;
	image.file_type = headerPCX.file_type;
	image.bits = headerPCX.numOfColorPlanes * 8;
}
bool ImagePCX::loadImageDataVGA(std::ifstream& stream, std::vector<uint8_t>& imageData, PagePCX& pcx, const uint32_t start, const uint32_t end)
{
	if (!isVGA(pcx.header) || !readVGA(stream, pcx, end))
	{
		pcx.msg = "Error during palete loading";
		return false;
	}
	stream.seekg(start + sizeof(HeaderPCX)); // Move back to start of image data
	if (pcx.header.encoding == 1)
	{
		decodeRLE(stream, imageData, pcx.header, end);
	}
	else
	{
		imageData.resize((pcx.image.width * pcx.image.height));
		stream.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
	}
	return true;
}
bool ImagePCX::convertImageDataVGA(const std::vector<uint8_t>& imageData, PagePCX& pcx)
{
	pcx.pixelData.resize(pcx.image.width * pcx.image.height * 3);
	pcx.header.numOfColorPlanes = 3;
	pcx.image.bits = 24;
	pcx.image.planar = true;
	int i = 0;
	int x, index;
	PixelRGB pRGB;
	for (int y = 0; y < pcx.image.height; y++)
	{
		for (x = 0; x < pcx.image.width; x++)
		{
			pRGB = pcx.palette[imageData[i]];
			index = y * 3 * pcx.image.width + x;
			pcx.pixelData[index] = pRGB.red;
			pcx.pixelData[index + pcx.image.width]= pRGB.green;
			pcx.pixelData[index + 2 * pcx.image.width] = pRGB.blue;
			i++;
		}
	}
	return true;
}
bool ImagePCX::readPCX(std::ifstream& stream, PagePCX& pcx, const uint32_t start, const uint32_t end)
{
	readHeader(stream, pcx.header, pcx.image);
	try
	{
		checkHeader(pcx.header, pcx.image);
	}
	catch (std::runtime_error& e)
	{
		pcx.msg = e.what();
		return false;
	}
	bool success = true;
	std::vector<uint8_t> imageData;
	switch (pcx.header.numOfColorPlanes)
	{
		case 1:
			pcx.image.palette = true;
			if (loadImageDataVGA(stream, imageData, pcx, start, end))
				success = convertImageDataVGA(imageData, pcx);
			else
				success = false;
			break;
		case 3:
		case 4:
			if (pcx.header.encoding == 0)
			{
				pcx.msg = "Uncompressed image data are not supported for 24 and 32 bit images";
				success = false;
			}
			else
			{
				//stream.seekg(start + sizeof(HeaderPCX));
				decodeRLE(stream, pcx.pixelData, pcx.header, end);
			}
			break;
		default:
			pcx.msg = "Unexpected number of color planes";
			return false;
	}
	return success;
}
void ImagePCX::loadImage()
{
	std::ifstream stream(filepath, std::ios::in | std::ios::binary);
	if (!stream)
	{
		this->technical.technicalMessage = "Unable to open file: " + image.name;
		return;
	}
	PagePCX pcx;
	pcx.image = image; // Sync with parent class version
	if (readPCX(stream, pcx, 0, calcFileEnd(stream)))
	{
		headerPCX = pcx.header;
		image = pcx.image;
		pixelData = pcx.pixelData;
		if (pcx.palette)
			paletteVGA = std::move(pcx.palette);
		this->technical.fileState = FileState::OK;
	}
}
void ImagePCX::decodeRLE(std::ifstream& inf, std::vector<uint8_t>& imageData, const HeaderPCX& headerPCX, const uint32_t end)
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
	while (inf.tellg() < end)
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
bool ImagePCX::isVGA(const HeaderPCX& headerPCX)
{
	return headerPCX.version == 5 && headerPCX.numOfColorPlanes == 1 && headerPCX.bitsPerPixel > 4;
}
const ImagePCX::HeaderPCX& ImagePCX::getHeader() const
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
void ImagePCX::checkHeader(const HeaderPCX& headerPCX, const ImageInfo& image)
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
	Pixel pixel;
	switch (headerPCX.numOfColorPlanes)
	{
		case 4:
			pixel.alpha = pixelData[x + ALPHA_OFFSET];
			/* no break */
		case 3:
			pixel.red = pixelData[x];
			pixel.green = pixelData[x + headerPCX.bytesPerLine];
			pixel.blue = pixelData[x + BLUE_OFFSET];
		break;
	}
	return pixel;
}
void ImagePCX::setPixel(int x, int y, Pixel newPixel)
{
	x = y * 3 * image.width + x;
	switch (headerPCX.numOfColorPlanes)
	{
		case 4:
			pixelData[x + 3 * image.width] = newPixel.alpha;
			/* no break */
		case 3:
			pixelData[x] = newPixel.red;
			pixelData[x + image.width]= newPixel.green;
			pixelData[x + 2 * image.width] = newPixel.blue;
		break;
	}
}
bool ImagePCX::savePCX(std::ofstream& stream, const PagePCX& pcx)
{
	if (!stream.is_open())
	{
		return false;
	}
	stream.write(reinterpret_cast<const char*>(&pcx.header), sizeof(HeaderPCX));
	switch (pcx.header.numOfColorPlanes)
	{
		case 3:
		case 4: writePlanarPixalData(stream, pcx.pixelData); break;
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
	outf.write(reinterpret_cast<const char*>(&headerPCX), sizeof(HeaderPCX));
	switch (headerPCX.numOfColorPlanes)
	{
		case 3:
		case 4: writePlanarPixalData(outf, pixelData); break;
		default:
			//this->fileStatus = "Unexpected number of color planes";
			outf.close();
			return false;
	}
	outf.close();
	return true;
}
void ImagePCX::writePlanarPixalData(std::ofstream& stream, const std::vector<unsigned char>& pixelData)
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
			stream.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
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
			stream.write(reinterpret_cast<const char*>(&numByte), sizeof(byte));
			stream.write(reinterpret_cast<const char*>(&lastByte), sizeof(byte));
			numByte = 0;
		}
	}
}
} /* namespace Images */
