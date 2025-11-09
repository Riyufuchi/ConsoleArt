//==============================================================================
// File       : ImagePPM.cpp
// Author     : riyufuchi
// Created on : Mar 17, 2024
// Last edit  : May 13, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImagePPM.h"

namespace Images
{
ImagePPM::ImagePPM(std::string filename) : Image(filename, ImageType::PPM)
{
	loadImage();
	image.width = headerPPM.width;
	image.height = headerPPM.height;
	image.file_type = 806;
}
ImagePPM::ImagePPM(std::string filename, int w, int h) : Image(filename, ImageType::PPM)
{
	headerPPM.width = w;
	headerPPM.height = h;
	pixelData.resize(w * h * 3);
	for (size_t x = 0; x < pixelData.size(); x++)
		pixelData.emplace_back(255);
	// Image info
	image.width = headerPPM.width;
	image.height = headerPPM.height;
	image.file_type = 806;
}
ImagePPM::~ImagePPM()
{
}
void ImagePPM::loadImage()
{
	std::ifstream inf(filepath, std::ios::in);
	if (!inf)
	{
		this->technical.technicalMessage = "Unable to open file: " + image.name;
		return;
	}
	std::string line;
	std::string byte;
	std::getline(inf, line);
	if (line != "P3" && line != "P6")
	{
		this->technical.technicalMessage = "Not a PPM file: " + image.name;
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
			this->technical.technicalMessage = "Missing width info";
			return;
		}
	}
	if (iss >> byte)
	{
		if (ConsoleLib::DataUtils::isNumber(byte))
			headerPPM.height = std::stoi(byte);
		else
		{
			this->technical.technicalMessage = "Missing height info";
			return;
		}
	}
	std::getline(inf, line);
	if (ConsoleLib::DataUtils::isNumber(line))
		headerPPM.maxColorVal = std::stoi(line);
	else
	{
		this->technical.technicalMessage = "Missing color info";
		return;
	}

	pixelData.resize(headerPPM.width * headerPPM.height * 3);
	size_t color = 0;
	while (std::getline(inf, line))
	{
		iss = std::istringstream(line);
		while (iss >> byte)
		{
			pixelData[color] = static_cast<uint8_t>(std::stoi(byte));
			color++;
		}
	}
	this->technical.fileState =  FileState::OK;
}
void ImagePPM::virtualArtistLegacy()
{
	headerPPM.width = 255;
	headerPPM.height = 255;
	pixelData.resize(headerPPM.width * headerPPM.height * 3);

	const int MOD = 256;

	for (int y = 0; y < headerPPM.height; y++)
		for (int x = 0; x < headerPPM.width; x++)
			setPixel(x, y, Pixel{(uint8_t)(x % MOD), (uint8_t)(y % MOD), (uint8_t)(x * y % MOD)});
	saveImage();
}
// Overrides
Pixel ImagePPM::getPixel(int x, int y) const
{
	return {pixelData[y * headerPPM.width + x], pixelData[y * headerPPM.width + x + 1], pixelData[y * headerPPM.width + x + 2]};
}
void ImagePPM::setPixel(int x, int y, Pixel newPixel)
{
	pixelData[y * headerPPM.width + x] = newPixel.red;
	pixelData[y * headerPPM.width + x + 1] = newPixel.green;
	pixelData[y * headerPPM.width + x + 2] = newPixel.blue;
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
