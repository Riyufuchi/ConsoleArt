//==============================================================================
// File       : AsciiPrinter.cpp
// Author     : riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Mar 4, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiPrinter.h"

namespace ConsoleArt
{
AsciiPrinter::AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console) : asciiCon(asCon), console(console)
{
	this->color = ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::CONSOLE_ART_UNIX_DEFAULT);
}
AsciiPrinter::AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleUtils::IConsole& console, ConsoleUtils::Color color) : asciiCon(asCon), console(console), color(color)
{
}
AsciiPrinter::~AsciiPrinter()
{
}
void AsciiPrinter::printPixelColored()
{
	#ifdef _WIN32
		console.out("Not supported in Windows version, because this application don't implement proper coloring for Windows console\n");
	#else
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
				switch (pixel.alpha)
				{
					case 0: std::cout << "  "; break;
					default: console.out(pixel.red, pixel.green, pixel.blue, "██");
				}
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
	#endif
}
void AsciiPrinter::printCharColored()
{
	#ifdef _WIN32
		console.out("Not supported in Windows, due to VS compiler complaints\n");
	#else
	Images::Image& image = asciiCon.getSourceImg();
	Images::Image::ImageInfo imageInfo = image.getImageInfo();
	Images::Image::Pixel pixel;
	const int HEIGHT = asciiCon.getSourceImg().getImageInfo().height - 1;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring utf32String;
	int xChar = 0;
	if (asciiCon.getSourceImg().isInverted())
	{
		for (int y = HEIGHT; y >= 0; y--)
		{
			utf32String = converter.from_bytes(asciiCon.getLine(y));
			for (int x = 0; x < imageInfo.width; x++)
			{
				pixel = image.getPixel(x, y);
				console.out(pixel.red, pixel.green, pixel.blue, converter.to_bytes(std::wstring(2, utf32String[xChar])));
				xChar += 2;
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
				pixel = image.getPixel(x, y);
				console.out(pixel.red, pixel.green, pixel.blue, converter.to_bytes(std::wstring(2, utf32String[xChar])));
				xChar += 2;
			}
			xChar = 0;
			std::cout << "\n";
		}
	}
	#endif
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
	console.out(ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::STRANGE), "Warning: Experimental!\n");
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
	ConsoleUtils::ColorPallete color = ConsoleUtils::ColorPallete::COMMUNITY;
	console.out(ConsoleUtils::ColorUtils::getColor(color), "File " + fName + " was successfully created.\n");
}
} /* namespace Images */
