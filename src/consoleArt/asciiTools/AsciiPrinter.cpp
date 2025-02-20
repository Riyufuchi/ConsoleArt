//==============================================================================
// File       : AsciiPrinter.cpp
// Author     : Riyufuchi
// Created on : Nov 22, 2023
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiPrinter.h"

namespace ConsoleArt
{
AsciiPrinter::AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleLib::IConsole& console) : asciiCon(asCon), console(console)
{
	this->color = ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::CONSOLE_ART_UNIX_DEFAULT);
}
AsciiPrinter::AsciiPrinter(ImageUtils::AsciiConverter& asCon, ConsoleLib::IConsole& console, ConsoleLib::Color color) : asciiCon(asCon), console(console), color(color)
{
}
AsciiPrinter::~AsciiPrinter()
{
}
void AsciiPrinter::printPixelColored()
{
	#ifdef _WIN32
		console.out("This option don't work properly in Windows, because of limits of Windows console."
				"Windows console don't implement ASCII Escape codes for coloring text, as Linux/Unix do.\n");
		console.out(ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::STRANGE), "Warning: Experimental!\n");
		if (!ConsoleUtility::ConsoleUtils::yesNo("Proceed anyway? [Y/n] "))
			return;
	#endif
	Images::Image& image = asciiCon.getSourceImg();
	const Images::ImageInfo& imageInfo = image.getImageInfo();
	Images::Pixel pixel;
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
}
void AsciiPrinter::printCharColored()
{
	#ifdef _WIN32
		console.out("Not supported in Windows, due to VS compiler complaints\n");
	#else
	Images::Image& image = asciiCon.getSourceImg();
	const Images::ImageInfo& imageInfo = image.getImageInfo();
	Images::Pixel pixel;
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
	console.enableCustomFG(color);
	if (asciiCon.getSourceImg().isInverted())
		for(int i = HEIGHT; i >= 0; i--)
			std::cout << asciiCon.getLine(i) << "\n";
	else
		for(int i = 0; i < HEIGHT; i++)
			std::cout << asciiCon.getLine(i) << "\n";
	console.disableCustomFG();
}
void AsciiPrinter::printToFile()
{
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
	console.out(ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::COMMUNITY),
			"File: " + fName + " was successfully created.\n");
}
} /* namespace Images */
