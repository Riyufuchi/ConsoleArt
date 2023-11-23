//==============================================================================
// File       : AsciiPrinter.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Nov 22, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiPrinter.h"

namespace ConsoleArt
{
AsciiPrinter::AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console) : asciiCon(asCon), console(console)
{
}

AsciiPrinter::~AsciiPrinter()
{
}
void AsciiPrinter::printPixelColored()
{
	Images::Image& image = asciiCon.getSourceImg();
	Images::Image::ImageInfo imageInfo = image.getImageInfo();
	Images::Image::Pixel pixel;
	const int HEIGHT = asciiCon.getSourceImg().getImageInfo().height - 1;
	for(int y = HEIGHT; y >= 0; y--)
	{
		for (int x = 0; x < imageInfo.width; x++)
		{
			pixel = image.getPixel(x, y);
			console.writeText(pixel.red, pixel.green, pixel.blue, "██");
		}
		std::cout << "\n";
	}
}
void AsciiPrinter::printCharColored()
{
	Images::Image& image = asciiCon.getSourceImg();
	Images::Image::ImageInfo imageInfo = image.getImageInfo();
	Images::Image::Pixel pixel;
	const int HEIGHT = asciiCon.getSourceImg().getImageInfo().height - 1;
	std::string line;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring utf32String;
	//wchar_t unicodeChar = utf32String[2]; // Access Unicode characters in wstring
	//std::wstring singleCharString(1, unicodeChar); // Convert wchar_t to std::wstring
	std::string convertedString; 	// Convert std::wstring to UTF-8 encoded string
	int xChar = 0;
	for(int y = HEIGHT; y >= 0; y--)
	{
		utf32String = converter.from_bytes(asciiCon.getLine(y));
		for (int x = 0; x < imageInfo.width; x++)
		{
			convertedString = converter.to_bytes(std::wstring(1, utf32String[xChar]));
			xChar += 2;
			pixel = image.getPixel(x, y);
			console.writeText(pixel.red, pixel.green, pixel.blue, convertedString);
			console.writeText(pixel.red, pixel.green, pixel.blue, convertedString);
		}
		xChar = 0;
		std::cout << "\n";
	}
}
void AsciiPrinter::printClassic()
{
	const int HEIGHT = asciiCon.getSourceImg().getImageInfo().height - 1;
	for(int i = HEIGHT; i >= 0; i--)
	{
		console.writeText(asciiCon.getLine(i));
	}
}
} /* namespace Images */
