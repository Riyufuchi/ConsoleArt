//==============================================================================
// File       : Image.cpp
// Author     : Riyufuchi
// Created on : Nov 20, 2023
// Last edit  : Nov 03, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Image.h"

namespace Images
{
Image::Image(std::string filepath) : filepath(filepath), fileStatus("Pending"), fileState(FileState::ERROR), inverted(false), positionBase(0)
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
bool Image::isLoaded()
{
	return fileState == OK;
}
bool Image::isInverted()
{
	return inverted;
}
} /* namespace Images */
