//==============================================================================
// File       : ImagePPM.cpp
// Author     : riyufuchi
// Created on : Mar 17, 2024
// Last edit  : Feb 17, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImagePPM.h"

namespace Images
{
ImagePPM::ImagePPM(std::string filename) : Image(filename)
{
	loadImage();
	imageInfo.name = this->filename;
	imageInfo.width = headerPPM.width;
	imageInfo.height = headerPPM.height;
	imageInfo.file_type = 806;
}
ImagePPM::ImagePPM(std::string filename, int w, int h) : Image(filename)
{
	headerPPM.width = w;
	headerPPM.height = h;
	imageData.reserve(w * h);
	for (size_t x = 0; x < imageData.size(); x++)
		imageData.emplace_back(Pixel{255, 255, 255});
	// Image info
	imageInfo.name = this->filename;
	imageInfo.width = headerPPM.width;
	imageInfo.height = headerPPM.height;
	imageInfo.file_type = 806;
}
ImagePPM::~ImagePPM()
{
}
void ImagePPM::loadImage()
{
	std::ifstream inf(filepath, std::ios::in);
	if (!inf)
	{
		this->fileStatus = "Unable to open file: " + filename;
		return;
	}
	std::string line;
	std::string byte;
	std::getline(inf, line);
	if (line != "P3" && line != "P6")
	{
		this->fileStatus = "Not a PPM file: " + filename;
		return;
	}

	std::getline(inf, line);
	std::istringstream iss(line);
	if (iss >> byte)
	{
		if (ConsoleLib::DataUtils::isNumber(byte))
			headerPPM.width = std::stoi(byte);
		else
		{
			this->fileStatus = "Missing width info";
			return;
		}
	}
	if (iss >> byte)
	{
		if (ConsoleLib::DataUtils::isNumber(byte))
			headerPPM.height = std::stoi(byte);
		else
		{
			this->fileStatus = "Missing height info";
			return;
		}
	}
	std::getline(inf, line);
	if (ConsoleLib::DataUtils::isNumber(line))
		headerPPM.maxColorVal = std::stoi(line);
	else
	{
		this->fileStatus = "Missing color info";
		return;
	}

	imageData.reserve(headerPPM.width * headerPPM.height);
	int color = 0;
	Pixel pixel;
	while (std::getline(inf, line))
	{
		iss = std::istringstream(line);
		while (iss >> byte)
		{
			switch (color)
			{
				case 0: pixel.red =  std::stoi(byte); break;
				case 1: pixel.green =  std::stoi(byte); break;
				case 2:
					pixel.blue =  std::stoi(byte);
					imageData.emplace_back(pixel);
					color = -1;
				break;
			}
			color++;
		}
	}
	this->fileState = OK;
}
void ImagePPM::virtualArtistLegacy()
{
	headerPPM.width = 255;
	headerPPM.height = 255;
	imageData.reserve(headerPPM.width * headerPPM.height * 3);

	const int MOD = 256;

	for (int y = 0; y < headerPPM.height; y++)
		for (int x = 0; x < headerPPM.width; x++)
			setPixel(x, y, Pixel{(uint8_t)(x % MOD), (uint8_t)(y % MOD), (uint8_t)(x * y % MOD)});
	saveImage();
}
// Overrides
Pixel ImagePPM::getPixel(int x, int y) const
{
	return imageData[y * headerPPM.width + x];
}
void ImagePPM::setPixel(int x, int y, Pixel newPixel)
{
	imageData[y * headerPPM.width + x] = newPixel;
}
bool ImagePPM::saveImage() const
{
	std::ofstream outf(filepath, std::ios::out | std::ios::trunc);
	if (!outf.is_open())
	{
		return false;
	}

	outf << headerPPM.format << "\n";
	outf << headerPPM.width << " " << headerPPM.height << "\n";
	outf << headerPPM.maxColorVal << "\n";

	Pixel p;
	const int MAX_X = headerPPM.width - 1;

	for (int y = 0; y < headerPPM.height; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			p = getPixel(x, y);
			outf << (int)p.red << " " << (int)p.green << " " << (int)p.blue << " ";
		}
		p = getPixel(MAX_X, y);
		outf << (int)p.red << " " << (int)p.green << " " << (int)p.blue << "\n";
	}
	outf.close();
	return true;
}
} /* namespace Images */
