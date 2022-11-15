//============================================================================
// Name        : AsciiConverter
// Author      : Riyufuchi
// Created on  : 15.11.2022 (Functionality from class ImageBMP)
// Last Edit   : 15.11.2022
// Description : This class converts bitmap image to ASCII/desired char set
//============================================================================


#include "AsciiConverter.h"

AsciiConverter::AsciiConverter(ImageBMP& img): sourceImg(img)
{
	this->sourceImg = img;
	this->brightness = 0;
	this->brightnessDiff = 0;
	this->ASCII_image = NULL;
	setCharSet(CHAR_SETS::BASIC);
}

void AsciiConverter::setCharSet(CHAR_SETS choice)
{
	setCharSet(static_cast<int>(choice));
}

void AsciiConverter::setCharSet(int choice)
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

std::string AsciiConverter::getLine(int index)
{
	//if((index > 0) && (index < bmp_info_header.height))
		return ASCII_image[index];
	//return " ";
}

void AsciiConverter::outputAsciiImage()
{
	if(ASCII_image == NULL)
		convertToASCII();
	const int height = ASCII_image->size();
	for(int i = 0; i < height; i++)
		std::cout << ASCII_image[i] << "\n";
}

void AsciiConverter::convertToASCII()
{
	std::string line = "";
	ImageBMP::BMPInfo imgInfo = sourceImg.getBmpInfo();
	const int HEIGHT = imgInfo.height;
	ASCII_image = new std::string[HEIGHT];
	int x = 0;
	int y = HEIGHT;
	ImageBMP::Pixel pix;
	int i = 0;
	int index = 0;
	const int DEF_BRIGHTNESS_DIFF = brightnessDiff;
	const int CHARSET_SIZE = chars.size();
	while (y > 0)
	{
		pix = sourceImg.getPixel(x, y);
		brightness = (pix.red * podR + pix.green * podG + pix.blue * podB);
		if (x < imgInfo.width)
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
			ASCII_image[index] = line;
			index++;
			//std::cout << line << "\n";
			line = "";
			y--;
			x = 0;
			std::cout << index << "/" << imgInfo.height << std::endl;
		}
		x++;
	}
}

AsciiConverter::~AsciiConverter()
{
	if(ASCII_image != NULL)
	{
		delete[] ASCII_image;
		ASCII_image = NULL;
	}
}
