//============================================================================
// Name        : AsciiConverter
// Author      : Riyufuchi
// Created on  : 15.11.2022 (Functionality from class ImageBMP)
// Last Edit   : Mar 03, 2024
// Description : This class converts bitmap image to ASCII/desired char set
//============================================================================

#include "../imageUtils/AsciiConverter.h"

namespace ImageUtils
{
AsciiConverter::AsciiConverter(Images::Image& img) : sourceImg(img)
{
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
	chars.clear();
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
		break;
		case BASIC_INVERTED:
			setCharSet(CHAR_SETS::BASIC);
			invertCharSet();
		break;
		case PRECISE_INVERTED:
			setCharSet(CHAR_SETS::PRECISE);
			invertCharSet();
		break;
		case DETAILED_INVERTED:
		{
			setCharSet(CHAR_SETS::DETAILED);
			invertCharSet();
			break;
		}
		case SHADES_INVERTED:
			setCharSet(CHAR_SETS::SHADES);
			invertCharSet();
		break;
		case SHADES:
			chars.push_back("  ");
			chars.push_back("░░");
			chars.push_back("▒▒");
			chars.push_back("▓▓");
			chars.push_back("██");
		break;
		default:
			setCharSet(CHAR_SETS::BASIC);
			std::cerr << "Input error - applied default settings\n";
		break;
	}
	brightnessDiff = std::ceil(255.0 / chars.size()); //NOTE: Changing brightnessDiff from int to double would also work
}

void AsciiConverter::invertCharSet()
{
	std::vector<std::string> newChars;
	const int MAX = chars.size() - 1;
	for(int i = MAX; i >= 0; i--)
	{
		newChars.push_back(chars.at(i));
	}
	chars = newChars;
}

Images::Image& AsciiConverter::getSourceImg()
{
	return sourceImg;
}

std::string AsciiConverter::getLine(int index)
{
	//if((index >= 0) && (index < bmp_info_header.height))
		return ASCII_image[index];
	//return " ";
}

void AsciiConverter::outputAsciiImage()
{
	if(!sourceImg.isLoaded())
		return;
	if(ASCII_image == NULL)
		convertToASCII();
	const int height = sourceImg.getImageInfo().height - 1;
	for(int i = height; i >= 0; i--)
		std::cout << ASCII_image[i] << "\n";
}

/**
 * Converts image into ASCII/UNICODE and save it into a string array
 */
void AsciiConverter::convertToASCII()
{
	if (!sourceImg)
		return;
	std::string line = "";
	Images::Image::Pixel pix;
	const int HEIGHT = sourceImg.getImageInfo().height;
	const int WIDTH = sourceImg.getImageInfo().width;
	int x = 0;
	int charID = 0;
	int index = 0;
	const int DEF_BRIGHTNESS_DIFF = brightnessDiff;
	const int CHARSET_SIZE = chars.size() - 1;
	ASCII_image = new std::string[HEIGHT];
	for(int y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			pix = sourceImg.getPixel(x, y);
			//std::cout << "X: " << x << "Y:" << y  << std::endl;
			brightness = (pix.red * RED_PART + pix.green * GREEN_PART + pix.blue * BLUE_PART);
			for (charID = 0; charID <= CHARSET_SIZE; charID++)
			{
				if (brightness <= brightnessDiff)
				{
					brightnessDiff = DEF_BRIGHTNESS_DIFF;
					break;
				}
				brightnessDiff += DEF_BRIGHTNESS_DIFF;
			}
			line.append(chars[charID]);
		}
		ASCII_image[index] = line;
		index++;
		line = "";
		std::cout << "#";
	}
	std::cout << "\nDone!" << std::endl;
}

AsciiConverter::~AsciiConverter()
{
	if(ASCII_image != NULL)
	{
		delete[] ASCII_image;
		ASCII_image = NULL;
	}
	std::cout << "AsciiConverter destructed" << std::endl;
}
}
