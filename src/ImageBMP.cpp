#include "ImageBMP.h"
/*
* Copyright Header
*
* Created On: 17.07.2020
* Last Edit: 08.11.2022
* Created By: Riyufuchi
*
*/

void ImageBMP::readBMP()
{
	using namespace std;
	ifstream inf(filename, ios::in);
	if (inf)
	{
		inf.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
		if (file_header.file_type != 0x4D42)
		{
			throw runtime_error("Error: Unrecognized format");
		}
		inf.read(reinterpret_cast<char*>(&bmp_info_header), sizeof(bmp_info_header));
		if (bmp_info_header.bit_count == 32)
		{
			if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader)))
			{
				inf.read(reinterpret_cast<char*>(&bmp_color_header), sizeof(bmp_color_header));
				if (check_color_header(bmp_color_header))
					throw runtime_error("An error has occurred");
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
			inf.read(reinterpret_cast<char*>(imgData.data()), imgData.size());
			file_header.file_size += imgData.size();
		}
		else
		{
			row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
			uint32_t new_stride = make_stride_aligned(4);
			vector<uint8_t> padding_row(new_stride - row_stride);
			for (int y = 0; y < bmp_info_header.height; ++y)
			{
				inf.read(reinterpret_cast<char*>(imgData.data() + row_stride * y), row_stride);
				inf.read(reinterpret_cast<char*>(padding_row.data()), padding_row.size());
			}
			file_header.file_size += imgData.size() + bmp_info_header.height * padding_row.size();
		}
		cout << "Image successfully loaded: " << filename << "\n";
	}
	else
	{
		cerr << "Unable to open file: " << filename << endl;
		this->filename = "NULL";
	}
}

bool ImageBMP::check_color_header(BMPColorHeader & bmp_color_header)
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

uint32_t ImageBMP::make_stride_aligned(uint32_t align_stride)
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

int ImageBMP::getRed(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	if (static_cast<int>(imgData[channels * (y * bmp_info_header.width + x) + 2]) < 0)
	{
		return imgData[channels * (y * bmp_info_header.width + x) + 2] * -1;
	}
	return static_cast<int>(imgData[channels * (y * bmp_info_header.width + x) + 2]);
}
int ImageBMP::getGreen(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	return static_cast<int>((imgData[channels * (y * bmp_info_header.width + x) + 1]) - 48);
}
int ImageBMP::getBlue(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	return static_cast<int>((imgData[channels * (y * bmp_info_header.width + x) + 0]) - 48);
}

ImageBMP::ImageBMP(const char* filename)
{
	this->filename = filename;
	this->brightness = 0;
	this->apa = NULL;
	setCharSet(CHAR_SETS::BASIC);
	try
	{
		readBMP();
	}
	catch (std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

ImageBMP::BMPInfo ImageBMP::getBmpInfo()
{
	BMPInfo a;
	a.name = this->filename;
	a.width = bmp_info_header.width;
	a.height = bmp_info_header.height;
	return a;
}

void ImageBMP::setCharSet(CHAR_SETS choice)
{
	setCharSet(static_cast<int>(choice));
}

void ImageBMP::setCharSet(int choice)
{
	switch (choice)
	{
		case BASIC:
			chars.push_back("██");//"▓▓");
			chars.push_back("##");
			chars.push_back("@@");
			chars.push_back("%%");
			chars.push_back("==");
			chars.push_back("++");
			chars.push_back("::");
			chars.push_back("--");
			chars.push_back("..");
			chars.push_back("  ");
			brightnessDiff = 255 / chars.size();
		break;
		case PRECISE:
			chars.push_back("██");
			chars.push_back("▒▒");
			chars.push_back("##");
			chars.push_back("@@");
			chars.push_back("%%");
			chars.push_back("==");
			chars.push_back("++");
			chars.push_back("**");
			chars.push_back("::");
			chars.push_back("--");
			chars.push_back("..");
			chars.push_back("  ");
			brightnessDiff = 22;
		break;
		case DETAILED:
			chars.push_back("██");
			chars.push_back("▓▓");
			chars.push_back("▒▒");
			chars.push_back("░░");
			chars.push_back("##");
			chars.push_back("@@");
			chars.push_back("%%");
			chars.push_back("xx");
			chars.push_back("==");
			chars.push_back("++");
			chars.push_back("**");
			chars.push_back("::");
			chars.push_back("--");
			chars.push_back("..");
			chars.push_back("  ");
			//brightnessDiff = 17;
			brightnessDiff = 255 / chars.size();
		break;
		case DETAILED_INVERTED:
		{
			setCharSet(CHAR_SETS::DETAILED);
			std::vector<std::string> newChars;
			const int NUM_OF_CHARS = chars.size() - 1;
			int selectIndex = NUM_OF_CHARS;
			for(int i = 0; i < NUM_OF_CHARS; i++)
			{
				newChars.push_back(chars.at(selectIndex));
				selectIndex--;
			}
			chars = newChars;
			break;
		}
		default:
			setCharSet(CHAR_SETS::BASIC);
			std::cerr << "Input error, default settings applied.\n";
		break;
	}
}

const char* ImageBMP::getFilename()
{
	return filename;
}

std::string ImageBMP::getLine(int index)
{
	//if((index > 0) && (index < bmp_info_header.height))
		return apa[index];
	//return " ";
}

void ImageBMP::outputAsciiImage()
{
	if(apa == NULL)
		convertToASCII();
	const int height = bmp_info_header.height;
	for(int i = 0; i < height; i++)
		std::cout << apa[i] << "\n";
}

void ImageBMP::convertToASCII()
{
	std::string line = "";
	const int HEIGHT = bmp_info_header.height;
	apa = new std::string[HEIGHT];
	int x = 0;
	int y = HEIGHT;
	Pixel pix;
	int i = 0;
	int index = 0;
	const int DEF_BRIGHTNESS_DIFF = brightnessDiff;
	const int CHARSET_SIZE = chars.size();
	while (y > 0)
	{
		pix = getPixel(x, y);
		brightness = (pix.red * podR + pix.green * podG + pix.blue * podB);
		if (x < bmp_info_header.width)
		{
			for (i = 0; i < CHARSET_SIZE; i++)
			{
				if (brightness < brightnessDiff)
				{
					brightnessDiff = DEF_BRIGHTNESS_DIFF;
					break;
				}
				brightnessDiff += DEF_BRIGHTNESS_DIFF;
			}
			//line = line + charSet[i] + charSet[i];
			line = line + chars.at(i);
		}
		else
		{
			apa[index] = line;
			index++;
			//std::cout << line << "\n";
			line = "";
			y--;
			x = 0;
			std::cout << index << "/" << bmp_info_header.height << std::endl;
		}
		x++;
	}
}

ImageBMP::~ImageBMP()
{
	if(apa != NULL)
	{
		delete[] apa;
		apa = NULL;
	}
	std::cout << "Image class destructed" << std::endl;
}
