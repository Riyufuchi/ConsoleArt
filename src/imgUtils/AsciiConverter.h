//============================================================================
// Name        : AsciiConverter
// Author      : Riyufuchi
// Created on  : 15.11.2022 (Functionality from class ImageBMP)
// Last Edit   : 15.11.2022
// Description : This class converts bitmap image to ASCII/desired char set
//============================================================================

#ifndef _AsciiConverter_H_
#define _AsciiConverter_H_

#include <vector>
#include <string.h>
#include "../ImageBMP.h"

class AsciiConverter
{
private:
	const double podR = 0.2989;
	const double podG = 0.5866;
	const double podB = 0.1145;
	int brightness;
	int brightnessDiff;
	std::vector<std::string> chars; //char set for conversion
	std::string* ASCII_image;
	ImageBMP& sourceImg;
public:
	//std::string precise2xIb[14] = {"  ", "██", "▓▓", "▒▒", "░░","##", "@@", "%%", "==", "++", "**", "::", "--", ".."};
	enum CHAR_SETS
		{
			BASIC,
			PRECISE,
			DETAILED,
			DETAILED_INVERTED
		};
	//ImageBMP is a reference not a pointer
	AsciiConverter(ImageBMP& img);
	void convertToASCII();
	void outputAsciiImage();
	//Setters
	void setCharSet(enum CHAR_SETS);
	void setCharSet(int choice);
	//Getters
	std::string getLine(int index);
	~AsciiConverter();
};
#endif
