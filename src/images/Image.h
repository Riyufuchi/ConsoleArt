//==============================================================================
// File       : Image.h
// Author     : riyufuchi
// Created on : Nov 20, 2023
// Last edit  : 01.12.2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGE_H_
#define IMAGES_IMAGE_H_

#include <iostream>
#include <fstream>

namespace Images
{
class Image
{
protected:
	std::string filename;
	std::string fileStatus;
	bool inverted;
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
		std::string name {"Error"};
		int width {0};
		int height {0};
		//int sizeInBytes;
		uint16_t bits {24};
		uint16_t file_type {0};
	};
	// Is methods
	bool isLoaded();
	bool isInverted();
	// Getters
	std::string getFilename();
	std::string getFileStatus();
	virtual ImageInfo getImageInfo() = 0;
	virtual Pixel getPixel(int x, int y) = 0;
	//Setters
	virtual void setPixel(int x, int y, Pixel newPixel) = 0;
};

} /* namespace Images */
#endif /* IMAGES_IMAGE_H_ */
