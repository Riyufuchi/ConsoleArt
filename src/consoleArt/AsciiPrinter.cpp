//==============================================================================
// File       : AsciiPrinter.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : 01.12.2023
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
	if (asciiCon.getSourceImg().isInverted())
	{
		const int HEIGHT = asciiCon.getSourceImg().getImageInfo().height - 1;
		for(int y = HEIGHT; y >= 0; y--)
		{
			for (int x = 0; x < imageInfo.width; x++)
			{
				pixel = image.getPixel(x, y);
				if (pixel.alpha > 0)
					console.out(pixel.red, pixel.green, pixel.blue, "██");
				else
					std::cout << "  ";
			}
			std::cout << "\n";
		}
	}
	else
	{
		for(int y = 0; y < imageInfo.height; y++)
		{
			for (int x = 0; x < imageInfo.width; x++)
			{
				pixel = image.getPixel(x, y);
				if (pixel.alpha > 0)
					console.out(pixel.red, pixel.green, pixel.blue, "██");
				else
					std::cout << "  ";
			}
			std::cout << "\n";
		}
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
	if (asciiCon.getSourceImg().isInverted())
	{
		for (int y = HEIGHT; y >= 0; y--)
		{
			utf32String = converter.from_bytes(asciiCon.getLine(y));
			for (int x = 0; x < imageInfo.width; x++)
			{
				convertedString = converter.to_bytes(std::wstring(1, utf32String[xChar]));
				xChar += 2;
				pixel = image.getPixel(x, y);
				console.out(pixel.red, pixel.green, pixel.blue, convertedString);
				console.out(pixel.red, pixel.green, pixel.blue, convertedString);
			}
			xChar = 0;
			std::cout << "\n";
		}
	}
	else
	{
		for (int y = 0; y < imageInfo.height; y++)
		{
			utf32String = converter.from_bytes(asciiCon.getLine(y));
			for (int x = 0; x < imageInfo.width; x++)
			{
				convertedString = converter.to_bytes(std::wstring(1, utf32String[xChar]));
				xChar += 2;
				pixel = image.getPixel(x, y);
				console.out(pixel.red, pixel.green, pixel.blue, convertedString);
				console.out(pixel.red, pixel.green, pixel.blue, convertedString);
			}
			xChar = 0;
			std::cout << "\n";
		}
	}
}
void AsciiPrinter::printClassic()
{
	const int HEIGHT = asciiCon.getSourceImg().getImageInfo().height - 1;
	console.setTextColor(color);
	if (asciiCon.getSourceImg().isInverted())
		for(int i = HEIGHT; i >= 0; i--)
			std::cout << asciiCon.getLine(i) << "\n";
	else
		for(int i = 0; i < HEIGHT; i++)
			std::cout << asciiCon.getLine(i) << "\n";
	console.resetTextColor();
}
void AsciiPrinter::printToFile()
{
	console.out(ConsoleUtils::Colors::getColor(ConsoleUtils::Colors::ColorPallete::STRANGE), "Warning: Experimental!\n");
	std::string fName = asciiCon.getSourceImg().getFilepath();
	fName = fName.substr(0, fName.find_last_of('.')) + ".txt";
	std::fstream file(fName, std::ios::out | std::ios::trunc);
	if (!file)
	{
		console.err("File error\n");
		return;
	}
	const int HEIGHT = asciiCon.getSourceImg().getImageInfo().height -1;
	if (asciiCon.getSourceImg().isInverted())
		for(int i = HEIGHT; i >= 0; i--)
			file << asciiCon.getLine(i) << "\n";
	else
		for(int i = 0; i < HEIGHT; i++)
			file << asciiCon.getLine(i) << "\n";
	file.close();
	ConsoleUtils::Colors::ColorPallete color = ConsoleUtils::Colors::ColorPallete::COMMUNITY;
	console.out(ConsoleUtils::Colors::getColor(color), "File " + fName + " was successfully created.\n");
}
} /* namespace Images */
