//============================================================================
// Name        : ImageBMP
// Author      : Riyufuchi
// Created on  : 17.07.2020
// Last Edit   : 05.03.2023
// Description : This class loads uncompressed 24 or 32 bit bitmap image
//============================================================================

#include "ImageBMP.h"

ImageBMP::ImageBMP(std::string filename)
{
	this->filename = filename;
	try
	{
		readBMP();
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		this->filename = "NULL";
	}
}

/*
 * TODO: Rewrite it to more readable form
 * TODO: Add comments
 */
void ImageBMP::readBMP()
{
	std::ifstream inf(filename, std::ios::in);
	if (!inf)
		throw std::runtime_error("Unable to open file");
	//Basic file info
	inf.read(reinterpret_cast<char*>(&file_header), sizeof(file_header)); //Reads and fill our file_header strut with data
	if (file_header.file_type != 0x4D42)
		throw std::runtime_error("Error: Unrecognized format");
	//BMP info and colors
	inf.read(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));
	if (bmp_info_header.bit_count == 32)
	{
		if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader)))
		{
			inf.read(reinterpret_cast<char*>(&bmp_color_header), sizeof(bmp_color_header));
			if (checkColorHeader(bmp_color_header))
				throw std::runtime_error("An error has occurred");
		}
		else
		{
			std::cerr << "Warning! The file " << filename << " does not seem to contain bit mask information\n";
			throw std::runtime_error("Error! Unrecognized file format");
		}
	}
	//Messy code
	inf.seekg(file_header.offset_data, inf.beg);
	if (bmp_info_header.bit_count == 32)
	{
		bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
		file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
	}
	else
	{
		bmp_info_header.size = sizeof(BMPInfoHeader);
		file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
	}
	file_header.file_size = file_header.offset_data;
	if (bmp_info_header.height < 0)
		throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
	imgData.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);
	if (bmp_info_header.width % 4 == 0)
	{
		inf.read(reinterpret_cast<char*>(imgData.data()), imgData.size());
		file_header.file_size += imgData.size();
	}
	else
	{
		row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
		uint32_t new_stride = makeStrideAligned(4);
		std::vector<uint8_t> padding_row(new_stride - row_stride);
		for (int y = 0; y < bmp_info_header.height; ++y)
		{
			inf.read(reinterpret_cast<char*>(imgData.data() + row_stride * y), row_stride);
			inf.read(reinterpret_cast<char*>(padding_row.data()), padding_row.size());
		}
		file_header.file_size += imgData.size() + bmp_info_header.height * padding_row.size();
	}
	std::cout << "Image: " << getFilename() << " successfully loaded\n";
}

bool ImageBMP::checkColorHeader(BMPColorHeader& bmp_color_header)
{
	BMPColorHeader expected_color_header;
	if (expected_color_header.red_mask != bmp_color_header.red_mask || expected_color_header.blue_mask != bmp_color_header.blue_mask || expected_color_header.green_mask != bmp_color_header.green_mask || expected_color_header.alpha_mask != bmp_color_header.alpha_mask)
	{
		std::cerr << "Unexpected color mask format! The program expects the pixel data to be in the BGRA format\n";
		return true;
	}
	if (expected_color_header.color_space_type != bmp_color_header.color_space_type)
	{
		std::cerr << "Unexpected color space type! The program expects sRGB values\n";
		return true;
	}
	return false;
}

uint32_t ImageBMP::makeStrideAligned(uint32_t align_stride)
{
	uint32_t new_stride = row_stride;
	while (new_stride % align_stride != 0)
	{
		new_stride++;
	}
	return new_stride;
}

ImageBMP::Pixel ImageBMP::getPixel(int x, int y)
{
	Pixel p;
	uint32_t channels = bmp_info_header.bit_count / 8;
	int posiotion = channels * (y * bmp_info_header.width + x);
	p.red = imgData[posiotion + 2];
	p.green = imgData[posiotion + 1];
	p.blue = imgData[posiotion]; // + 0
	return p;
}

uint8_t ImageBMP::getRed(int x, int y)
{
	return imgData[(bmp_info_header.bit_count / 8) * (y * bmp_info_header.width + x) + 2]; //static_cast<int>(imgData[x])
}
uint8_t ImageBMP::getGreen(int x, int y)
{
	return imgData[(bmp_info_header.bit_count / 8) * (y * bmp_info_header.width + x) + 1];
}
uint8_t ImageBMP::getBlue(int x, int y)
{
	return imgData[(bmp_info_header.bit_count / 8) * (y * bmp_info_header.width + x)];
}

uint8_t ImageBMP::getAplha(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	if (channels == 4)
		return imgData[channels * (y * bmp_info_header.width + x) + 3];
	else
		return 255;
}

ImageBMP::BMPInfo ImageBMP::getBmpInfo()
{
	BMPInfo a;
	a.name = getFilename();
	a.width = bmp_info_header.width;
	a.height = bmp_info_header.height;
	return a;
}

std::string ImageBMP::getFilename()
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

//NOTE: Needs better implementation, but it is good for now
bool ImageBMP::isLoaded()
{
	return filename != std::string("NULL");
}

ImageBMP::~ImageBMP()
{
	std::cout << "Image class with: " << getFilename() << " destructed successfully" << std::endl;
}
