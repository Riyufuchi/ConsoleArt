//==============================================================================
// File       : Image.cpp
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Mar 22, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Image.h"

namespace Images
{
Image::Image(std::string filepath) : filepath(filepath), fileStatus("Pending"), inverted(false)
{
	size_t xPos;
	if ((xPos = filepath.find_last_of('/')) != std::string::npos)
		this->filename = filepath.substr(xPos + 1);
	else
		this->filename = filepath;

}
void Image::rename(std::string imageName)
{
	imageName = imageName.append(filename.substr(filename.find('.')));
	filepath = filepath.substr(0, (filepath.length() - filename.length())).append(imageName);
	filename = imageName;
}
const std::string& Image::getFileStatus() const
{
	return fileStatus;
}
const std::string& Image::getFilename() const
{
	return filename;
}
const std::string& Image::getFilepath() const
{
	return filepath;
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
	return fileStatus == "OK";
}
bool Image::isInverted()
{
	return inverted;
}
} /* namespace Images */
