//==============================================================================
// File       : ImageGIF.cpp
// Author     : riyufuchi
// Created on : Nov 6, 2025
// Last edit  : Nov 6, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageGIF.h"

#include "../include/stb_image.h"

namespace Images
{

ImageGIF::ImageGIF(const std::string& filepath) : Image(filepath)
{
	loadImage();
}

ImageGIF::~ImageGIF()
{
}

void ImageGIF::loadImage()
{
	int width = 0, height = 0, frameCount = 0, channels = 0;
	int* delayArr = nullptr;
	// Read file into memory
	std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);
	if (!ifs)
	{
		technical.technicalMessage = "Failed to open file.";
		return;
	}
	std::streamsize size = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	std::vector<unsigned char> buffer(size);
	if (!ifs.read((char*)buffer.data(), size))
	{
		technical.technicalMessage = "Failed to read file.";
		return;
	}
	unsigned char* data = stbi_load_gif_from_memory(buffer.data(), (int)buffer.size(), &delayArr, &width, &height, &frameCount, &channels, 4);

	if (!data)
	{
		technical.technicalMessage = stbi_failure_reason();
		return;
	}

	const size_t frameSize = static_cast<size_t>(width) * height * 4;
	frames.resize(frameCount);
	delays.resize(frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		frames[i].resize(frameSize);
		std::memcpy(frames[i].data(), data + i * frameSize, frameSize);
		delays[i] = delayArr ? delayArr[i] : 100;
	}

	// Fill Image base info
	image.width = width;
	image.height = height;
	image.bits = 32;
	technical.channels = 4;
	technical.fileState = FileState::OK;
	technical.pixelByteOrder = PixelByteOrder::RGBA;
	technical.technicalMessage = "GIF loaded successfully";

	// Keep first frame as default pixelData
	pixelData = frames[0];

	stbi_image_free(data);
	if (delayArr)
		free(delayArr); // stb allocates it with malloc
}

Images::Pixel ImageGIF::getPixel(int , int ) const
{
	return {};
}

void ImageGIF::setPixel(int , int , Images::Pixel )
{
}

bool ImageGIF::saveImage() const
{
	return false;
}

} /* namespace sdl */
