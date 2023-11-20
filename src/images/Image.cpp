//==============================================================================
// File       : Image.cpp
// Author     : riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Nov 20, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Image.h"

namespace Images
{

Image::Image(std::string filename) : filename(filename)
{
}
Image::~Image()
{
}
std::string Image::getFilename()
{
	return filename.substr(filename.find_last_of('/') + 1, filename.length() + 1);
}
/*const char* ImageBMP::getFilename()
{
	int i = 0;
	while (filename[i] != '\0')
			++i;
	int x = i;
	for (; x > 0; x--)
		if(filename[x] == '/')
			break;
	char* name = new char[i + 1];
	for(int y = 0; y < i; y++)
	{
		name[y] = filename[x];
		++x;
	}
	name[x++] = '\0';
	return name;
}*/
bool Image::isLoaded()
{
	return filename != std::string("NULL");
}
} /* namespace Images */
