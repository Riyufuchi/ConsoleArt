//==============================================================================
// File       : AsciiPrinterCLI.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../console_art/cli/AsciiPrinterCLI.h"

namespace consoleart
{
AsciiPrinterCLI::AsciiPrinterCLI(consolelib::IConsole& console) : AbstractAsciiPrinter(), console(console)
{
}

AsciiPrinterCLI::~AsciiPrinterCLI()
{
}

void AsciiPrinterCLI::printPixelColored()
{
	if (!converter)
		return;
	consoleartlib::Image& image = converter->getSourceImg();
	const consoleartlib::ImageInfo& imageInfo = image.getImageInfo();
	consoleartlib::Pixel pixel;
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
	consoleartlib::Image& image = converter->getSourceImg();
	const consoleartlib::ImageInfo& imageInfo = image.getImageInfo();
	consoleartlib::Pixel pixel;
	const int HEIGHT = converter->getSourceImg().getImageInfo().height - 1;
	size_t xChar = 0;
	std::string ch;

	auto renderLine = [&](int y)
	{
		auto u32line = consolelib::data_tools::string_to_u32string(converter->getLine(y));
		xChar = 0;
		for (int x = 0; x < imageInfo.width; x++)
		{
			pixel = image.getPixel(x, y);

			ch = consolelib::data_tools::u32char_to_string(u32line[xChar]);

			console.out(pixel.red, pixel.green, pixel.blue, ch + ch);
			xChar += 2;
		}

		std::cout << '\n';
	};

	if (converter->getSourceImg().isInverted())
		for (int y = HEIGHT; y >= 0; y--)
			renderLine(y);
	else
		for (int y = 0; y < imageInfo.height; y++)
			renderLine(y);
}

} /* namespace consoleart */
