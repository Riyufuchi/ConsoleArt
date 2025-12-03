//============================================================================
// Name        : AsciiConverter
// Author      : Riyufuchi
// Created on  : 15.11.2022 (Functionality from class ImageBMP)
// Last Edit   : Nov 19, 2025
// Description : This class converts bitmap image to ASCII/desired char set
//============================================================================

#ifndef _AsciiConverter_H_
#define _AsciiConverter_H_

#include <vector>
#include <cmath>
#include <string.h>
#include <memory>
#include "../../images/base/Image.h"

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
	consoleartlib::Image& sourceImg;
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
		PRECISE_INVERTED,
		SHADES,
		SHADES_INVERTED,
		CHAR_SETS_COUNT
	};
	AsciiConverter(consoleartlib::Image& img);
	//Procedures
	bool convertToASCII();
	void outputAsciiImage();
	//Setters
	void setCharSet(enum CHAR_SETS);
	void setCharSet(int choice);
	//Getters
	std::string getLine(int index);
	consoleartlib::Image& getSourceImg();
	~AsciiConverter();
};
}
#endif
