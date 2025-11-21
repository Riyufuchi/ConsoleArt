//==============================================================================
// File       : AsciiPrinterCLI.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Mar 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiPrinterCLI.h"

namespace ConsoleArt
{
AsciiPrinterCLI::AsciiPrinterCLI(ConsoleLib::IConsole& console) : AbstractAsciiPrinter(), console(console)
{
}

AsciiPrinterCLI::~AsciiPrinterCLI()
{
}

void AsciiPrinterCLI::printPixelColored()
{
	if (!converter)
		return;
	Images::Image& image = converter->getSourceImg();
	const Images::ImageInfo& imageInfo = image.getImageInfo();
	Images::Pixel pixel;
	if (converter->getSourceImg().isInverted())
	{
		const int HEIGHT = converter->getSourceImg().getImageInfo().height - 1;
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

void AsciiPrinterCLI::printToFile()
{
	std::string result;
	if (AbstractAsciiPrinter::printToFile(result))
		console.out(result.append("\n"));
	else
		console.err(result.append("\n"));
}

void AsciiPrinterCLI::printClassic()
{
	if (!converter)
		return;
	const int HEIGHT = converter->getSourceImg().getImageInfo().height - 1;
	console.enableCustomFG();
	if (converter->getSourceImg().isInverted())
		for(int i = HEIGHT; i >= 0; i--)
			std::cout << converter->getLine(i) << "\n";
	else
		for(int i = 0; i < HEIGHT; i++)
			std::cout << converter->getLine(i) << "\n";
	console.disableCustomFG();
}

void AsciiPrinterCLI::printCharColored()
{
	if (!converter)
		return;
	#ifdef _WIN32
		console.err("Not supported in Windows, due to MS compiler complaints\n");
	#else
	Images::Image& image = converter->getSourceImg();
	const Images::ImageInfo& imageInfo = image.getImageInfo();
	Images::Pixel pixel;
	const int HEIGHT = converter->getSourceImg().getImageInfo().height - 1;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wCharConverter;
	std::wstring utf32String;
	int xChar = 0;
	if (converter->getSourceImg().isInverted())
	{
		for (int y = HEIGHT; y >= 0; y--)
		{
			utf32String = wCharConverter.from_bytes(converter->getLine(y));
			for (int x = 0; x < imageInfo.width; x++)
			{
				pixel = image.getPixel(x, y);
				console.out(pixel.red, pixel.green, pixel.blue, wCharConverter.to_bytes(std::wstring(2, utf32String[xChar])));
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
			utf32String = wCharConverter.from_bytes(converter->getLine(y));
			for (int x = 0; x < imageInfo.width; x++)
			{
				pixel = image.getPixel(x, y);
				console.out(pixel.red, pixel.green, pixel.blue, wCharConverter.to_bytes(std::wstring(2, utf32String[xChar])));
				xChar += 2;
			}
			xChar = 0;
			std::cout << "\n";
		}
	}
	#endif
}

} /* namespace ConsoleArt */
