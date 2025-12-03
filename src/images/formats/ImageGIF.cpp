//==============================================================================
// File       : ImageGIF.cpp
// Author     : riyufuchi
// Created on : Nov 06, 2025
// Last edit  : Nov 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "ImageGIF.h"

#include "../utils/stb_image.h"
#include "../utils/stb_image_write.h"

namespace consoleartlib
{

ImageGIF::ImageGIF(const std::string& filepath) : Image(filepath, ImageType::GIF), selectedFrameIndex(0)
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
	image.channels = 4;
	image.pixelByteOrder = PixelByteOrder::RGBA;
	technical.fileState = FileState::OK;
	technical.technicalMessage = "GIF loaded successfully";
	if (frameCount > 1)
	{
		image.animated = true;
		image.multipage = true;
	}

	// Keep first frame as default pixelData
	pixelData = frames[0];

	stbi_image_free(data);
	if (delayArr)
		free(delayArr); // stb allocates it with malloc
}

consoleartlib::Pixel ImageGIF::getPixel(int x, int y) const
{
	x = (y * image.width + x) * image.channels;
	return {pixelData[x], pixelData[x + 1], pixelData[x + 2], pixelData[x + 3]};
}

void ImageGIF::setPixel(int x, int y, consoleartlib::Pixel pixel)
{
	x = (y * image.width + x) * image.channels;
	pixelData[x] = pixel.red;
	pixelData[x + 1] = pixel.green;
	pixelData[x + 2] = pixel.blue;
	pixelData[x + 3] = pixel.alpha;
}

bool ImageGIF::saveImage() const
{
	return false;
}

const std::vector<uint8_t>& ImageGIF::getFrame(int index) const
{
	return frames[index];
}

void ImageGIF::selectPage(size_t index)
{
	if (index < frames.size())
	{
		pixelData = frames[index];
		selectedFrameIndex = index;
	}
}

size_t ImageGIF::getSelectedPageIndex() const
{
	return selectedFrameIndex;
}

int ImageGIF::getFrameDelay(size_t index) const
{
	return delays[index];
}

bool ImageGIF::spitIntoPNGs() const
{
	int index = 0;
	std::string name = getFilename();
	name.replace(name.length() - 4, name.length(), ".png");
	for (const std::vector<uint8_t>& pixelData : frames)
	{
		stbi_write_png((std::to_string(index) + "-" + name).c_str(), image.width, image.height, image.channels, pixelData.data(), image.width * image.channels);
		index++;
	}
	return true;
}

size_t ImageGIF::getPageCount() const
{
	return frames.size();
}

} /* namespace sdl */
