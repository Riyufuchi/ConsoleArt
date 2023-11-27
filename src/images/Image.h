//==============================================================================
// File       : Image.h
// Author     : riyufuchi
// Created on : Nov 20, 2023
// Last edit  : 27.11.2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGE_H_
#define IMAGES_IMAGE_H_

#include <iostream>

namespace Images
{
class Image
{
protected:
	std::string filename;
	std::string fileStatus;
private:

public:
	Image(std::string filename);
	virtual ~Image();
	explicit operator bool() const
	{
		return fileStatus == "OK";
	}
	struct Pixel
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha {255};
	};
	struct ImageInfo
	{
		std::string name;
		int width;
		int height;
		//int sizeInBytes;
		uint16_t file_type;
	};
	// Is methods
	bool isLoaded();
	// Getters
	std::string getFilename();
	std::string getFileStatus();
	virtual ImageInfo getImageInfo() = 0;
	virtual Pixel getPixel(int x, int y) = 0;
	virtual uint8_t getRed(int x, int y) = 0;
	virtual uint8_t getGreen(int x, int y) = 0;
	virtual uint8_t getBlue(int x, int y) = 0;
	virtual uint8_t getAplha(int x, int y) = 0;
};

} /* namespace Images */
#endif /* IMAGES_IMAGE_H_ */
