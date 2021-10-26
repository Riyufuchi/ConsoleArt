#include "Image.h"

/*
* Copyright Header
*
* Created On: 17.07.2020
* Last Edit: 26.10.2021
* Created By: Riyufuchi
*
*/

void Image::readBMP()
{
	using namespace std;
	ifstream inf(filename, ios::in);
	if (inf)
	{
		inf.read((char*)&file_header, sizeof(file_header));
		if (file_header.file_type != 0x4D42)
		{
			throw runtime_error("Error: Unrecognized format");
		}
		inf.read((char*)&bmp_info_header, sizeof(bmp_info_header));
		if (bmp_info_header.bit_count == 32)
		{
			if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader)))
			{
				inf.read((char*)&bmp_color_header, sizeof(bmp_color_header));
				check_color_header(bmp_color_header);
			}
			else
			{
				cerr << "Warning! The file \"" << filename << "\" does not seem to contain bit mask information\n";
				throw std::runtime_error("Error! Unrecognized file format");
			}
		}
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
		{
			throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
		}
		imgData.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);
		if (bmp_info_header.width % 4 == 0)
		{
			inf.read((char*)imgData.data(), imgData.size());
			file_header.file_size += imgData.size();
		}
		else
		{
			row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
			uint32_t new_stride = make_stride_aligned(4);
			vector<uint8_t> padding_row(new_stride - row_stride);
			for (int y = 0; y < bmp_info_header.height; ++y)
			{
				inf.read((char*)(imgData.data() + row_stride * y), row_stride);
				inf.read((char*)padding_row.data(), padding_row.size());
			}
			file_header.file_size += imgData.size() + bmp_info_header.height * padding_row.size();
		}
		cout << "Img successfully loaded: " << filename << "\n";
	}
	else
	{
		cerr << "Unable to open file: " << filename << "\n";
	}
}

void Image::check_color_header(BMPColorHeader & bmp_color_header)
{
	BMPColorHeader expected_color_header;
	if (expected_color_header.red_mask != bmp_color_header.red_mask || expected_color_header.blue_mask != bmp_color_header.blue_mask || expected_color_header.green_mask != bmp_color_header.green_mask || expected_color_header.alpha_mask != bmp_color_header.alpha_mask)
	{
		throw std::runtime_error("Unexpected color mask format! The program expects the pixel data to be in the BGRA format");
	}
	if (expected_color_header.color_space_type != bmp_color_header.color_space_type)
	{
		throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
	}
}

uint32_t Image::make_stride_aligned(uint32_t align_stride)
{
	uint32_t new_stride = row_stride;
	while (new_stride % align_stride != 0)
	{
		new_stride++;
	}
	return new_stride;
}

Image::Pixel Image::getPixel(int x, int y)
{
	Pixel p;
	uint32_t channels = bmp_info_header.bit_count / 8;
	p.red = (imgData[channels * (y * bmp_info_header.width + x) + 2]);
	if (p.red < 0)
	{
		p.red *= -1;
	}
	p.green = imgData[channels * (y * bmp_info_header.width + x) + 1];
	if (p.green < 0)
	{
		p.green *= -1;
	}
	p.blue = imgData[channels * (y * bmp_info_header.width + x) + 0];
	if (p.blue < 0)
	{
		p.blue *= -1;
	}
	return p;
}

int Image::getRed(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	if((int)imgData[channels * (y * bmp_info_header.width + x) + 2] < 0)
	{
		return imgData[channels * (y * bmp_info_header.width + x) + 2] * -1;
	}
	return (int)imgData[channels * (y * bmp_info_header.width + x) + 2];
}
int Image::getGreen(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	return (int)((imgData[channels * (y * bmp_info_header.width + x) + 1])-48);
}
int Image::getBlue(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	return (int)((imgData[channels * (y * bmp_info_header.width + x) + 0])-48);
}

Image::Image(const char* filename)
{
	this->filename = filename;
	setCharSet(CHAR_SETS::DETAILED_INVERTED);
	readBMP();
}

Image::BMPInfo Image::getBmpInfo()
{
	BMPInfo a;
	a.name = this->filename;
	a.width = bmp_info_header.width;
	a.height = bmp_info_header.height;
	return a;
}

void Image::setCharSet(CHAR_SETS choice)
{
	switch (choice)
	{
		case BASIC: charSet = "█#@%=+:-. "; charSetSize = 10; break; //Basic - Classic
		case PRECISE:  charSet = "█▒#@%=+*:-. "; charSetSize = 12; break; //Precise - Classic
		case DETAILED: charSet = "█▓▒░#@%x=+*:-. "; charSetSize = 15; break; //More Precise - Classic
		case DETAILED_INVERTED: charSet = " .-:*+=x%@#░▒▓█"; charSetSize = 15; break; //More Precise - Inverted
	}
}

void Image::convertToASCII()
{
	std::string line = "";
	int brightness;
	int x = 0;
	int y = bmp_info_header.height;
	int brightnessDif = 17;
	Pixel pix;
	int i = 0;
	while (y > -1)
	{
		pix = getPixel(x, y);
		brightness = (pix.red * podR + pix.green * podG + pix.blue * podB);
		if (x < bmp_info_header.width)
		{
			for (i = 0; i < charSetSize; i++)
			{
				if (brightness < brightnessDif)
				{
					brightnessDif = 17;
					break;
				}
				brightnessDif += 17;
			}
			line = line + charSet[i] + charSet[i];
		}
		else
		{
			std::cout << line << "\n";
			line = "";
			y--;
			x = 0;
		}
		x++;
	}
}

void Image::imgToArray()
{
	std::string line = "";
	const int h = bmp_info_header.height;
	apa = new std::string[h];
	int brightness = 0;
	int x = 0;
	int y = h;
	Pixel pix;
	int i = 0;
	int brightnessDif = 17;
	int index = 0;
	while (y > 0)
	{
		pix = getPixel(x, y);
		brightness = (pix.red * podR + pix.green * podG + pix.blue * podB);
		if (x < bmp_info_header.width)
		{
			for (i = 0; i < 15; i++)
			{
				if (brightness < brightnessDif)
				{
					brightnessDif = 17;
					break;
				}
				brightnessDif += 17;
			}
			line = line + charSet[i] + charSet[i];
		}
		else
		{
			apa[index] = line;
			index++;
			//std::cout << line << "\n";
			line = "";
			y--;
			x = 0;
			std::cout << y << "/" << bmp_info_header.height << std::endl;
		}
		x++;
	}
}

Image::~Image()
{
	delete apa, charSet;
}
