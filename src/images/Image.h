//==============================================================================
// File       : Image.h
// Author     : riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Feb 22, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef IMAGES_IMAGE_H_
#define IMAGES_IMAGE_H_

#include <iostream>
#include <fstream>
#include <cstdint>

namespace Images
{
class Image
{
protected:
	std::string filepath;
	std::string fileStatus;
	bool inverted;
private:
	std::string filename;
public:
	Image(std::string filepath);
	virtual ~Image() = default;
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
	virtual const bool saveImage() = 0;
	// Is methods
	bool isLoaded();
	bool isInverted();
	// Getters
	const std::string& getFilename() const;
	const std::string& getFilepath() const;
	const std::string& getFileStatus() const;
	virtual ImageInfo getImageInfo() = 0;
	virtual Pixel getPixel(int x, int y) = 0;
	//Setters
	virtual void setPixel(int x, int y, Pixel newPixel) = 0;
};

} /* namespace Images */
#endif /* IMAGES_IMAGE_H_ */
