//==============================================================================
// File       : Image.h
// Author     : riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Nov 20, 2023
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
private:

public:
	Image(std::string filename);
	virtual ~Image();
	explicit operator bool() const
	{
		return filename != std::string("NULL");
	}
	// Is methods
	bool isLoaded();
	// Getters
	std::string getFilename();
	virtual uint8_t getRed(int x, int y) = 0;
	virtual uint8_t getGreen(int x, int y) = 0;
	virtual uint8_t getBlue(int x, int y) = 0;
	virtual uint8_t getAplha(int x, int y) = 0;
};

} /* namespace Images */
#endif /* IMAGES_IMAGE_H_ */
