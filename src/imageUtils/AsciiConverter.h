//============================================================================
// Name        : AsciiConverter
// Author      : Riyufuchi
// Created on  : 15.11.2022 (Functionality from class ImageBMP)
// Last Edit   : 20.11.2023
// Description : This class converts bitmap image to ASCII/desired char set
//============================================================================

#ifndef _AsciiConverter_H_
#define _AsciiConverter_H_

#include <vector>
#include <cmath>
#include <string.h>
#include "../images/ImageBMP.h"

namespace ImageUtils
{
class AsciiConverter
{
private:
	const double RED_PART = 0.2989;
	const double GREEN_PART = 0.5866;
	const double BLUE_PART = 0.1145;
	int brightness;
	int brightnessDiff;
	std::vector<std::string> chars; //char set for conversion
	std::string* ASCII_image;
	Images::ImageBMP& sourceImg;
	void invertCharSet();
public:
	//std::string precise2xIb[14] = {"  ", "██", "▓▓", "▒▒", "░░","##", "@@", "%%", "==", "++", "**", "::", "--", ".."};
	enum CHAR_SETS
	{
		BASIC,
		PRECISE,
		DETAILED,
		DETAILED_INVERTED,
		BASIC_INVERTED,
		PRECISE_INVERTED
	};
	AsciiConverter(Images::ImageBMP& img);
	//Procedures
	void convertToASCII();
	void outputAsciiImage();
	//Setters
	void setCharSet(enum CHAR_SETS);
	void setCharSet(int choice);
	//Getters
	std::string getLine(int index);
	~AsciiConverter();
};
}
#endif
