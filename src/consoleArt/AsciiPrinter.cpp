//==============================================================================
// File       : AsciiPrinter.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : 23.11.2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiPrinter.h"

namespace ConsoleArt
{
AsciiPrinter::AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console) : asciiCon(asCon), console(console)
{
	this->color = ConsoleUtils::Colors::getColor(ConsoleUtils::Colors::ColorPallete::CONSOLE_ART_UNIX_DEFAULT);
}
AsciiPrinter::AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console, ConsoleUtils::Colors::Color color) : asciiCon(asCon), console(console), color(color)
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
	std::string convertedString;
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
	console.setTextColor(color);
	for(int i = HEIGHT; i >= 0; i--)
	{
		//console.writeText(asciiCon.getLine(i));
		std::cout << asciiCon.getLine(i) << "\n";
	}
	console.resetTextColor();
}
void AsciiPrinter::printToFile()
{
}
} /* namespace Images */
