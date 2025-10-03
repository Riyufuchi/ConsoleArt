//==============================================================================
// File       : Dithering.cpp
// Author     : riyufuchi
// Created on : Mar 18, 2025
// Last edit  : Sep 22, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Dithering.h"

namespace ImageUtils {

Dithering::Dithering()
{
	this->minecraftPalette = {
		    {255, 255, 255}, {200, 200, 200}, {150, 150, 150}, // Whites and grays
		    {100, 100, 100}, {50, 50, 50}, {0, 0, 0},         // Darker shades
		    {255, 0, 0}, {200, 50, 50}, {150, 75, 75},       // Reds
		    {0, 255, 0}, {50, 200, 50}, {75, 150, 75},       // Greens
		    {0, 0, 255}, {50, 50, 200}, {75, 75, 150},       // Blues
		    {255, 255, 0}, {255, 165, 0}, {139, 69, 19},     // Yellow, Orange, Brown
		    {34, 139, 34}, {0, 128, 255}, {128, 0, 128},     // Grass Green, Water, Purple
		    {250, 240, 190}, {210, 180, 140}                 // Sand and dirt-like tones
		};
	/*{
		{255, 255, 255}, {200, 200, 200}, {150, 150, 150}, // White to Light Gray
		{100, 100, 100}, {50, 50, 50}, {0, 0, 0},         // Darker Grays and Black
		{255, 0, 0}, {0, 255, 0}, {0, 0, 255},           // Red, Green, Blue
		{255, 255, 0}, {255, 165, 0}, {139, 69, 19},     // Yellow, Orange, Brown
		{34, 139, 34}, {0, 128, 255}, {128, 0, 128}      // Grass Green, Water, Purple
	};*/
}

Dithering::~Dithering()
{
}

// Find the closest color from the palette
Images::PixelRGB Dithering::findClosestColor(uint8_t r, uint8_t g, uint8_t b)
{
	Images::PixelRGB bestMatch = minecraftPalette[0];
	int bestDist = std::numeric_limits<int>::max();
	int dr, dg, db, dist;

	for (const Images::PixelRGB& color : minecraftPalette)
	{
		dr = r - color.red;
		dg = g - color.green;
		db = b - color.blue;
		dist = dr * dr + dg * dg + db * db;

		if (dist < bestDist)
		{
			bestDist = dist;
			bestMatch = color;
		}
	}
	return bestMatch;
}

void Dithering::ditherImage(std::string imagepath)
{
	int width, height, channels;
	uint8_t *img = stbi_load(imagepath.c_str(), &width, &height, &channels, 3);

	if (!img)
	{
		std::cerr << "Failed to load image[" << imagepath << "]\n";
		return;
	}

	std::vector<uint8_t> ditheredImg(width * height * 3);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int index = (y * width + x) * 3;
			uint8_t r = img[index];
			uint8_t g = img[index + 1];
			uint8_t b = img[index + 2];

			// Get the closest palette color
			Images::PixelRGB newColor = findClosestColor(r, g, b);
			ditheredImg[index] = newColor.red;
			ditheredImg[index + 1] = newColor.green;
			ditheredImg[index + 2] = newColor.blue;

			// Error correction, but **less aggressive**
			//int errorR = (r - newColor.red) / 2;  // Reduce error spread
			//int errorG = (g - newColor.green) / 2;
			//int errorB = (b - newColor.blue) / 2;

			// Spread error to neighboring pixels
			/*auto spreadError = [&](int dx, int dy, float factor)
			{
				int nx = x + dx, ny = y + dy;
				if (nx >= 0 && nx < width && ny >= 0 && ny < height)
				{
					int neighborIndex = (ny * width + nx) * 3;
					img[neighborIndex] = std::clamp((int)(img[neighborIndex] + errorR * factor), 0, 255);
					img[neighborIndex + 1] = std::clamp((int)(img[neighborIndex + 1] + errorG * factor), 0, 255);
					img[neighborIndex + 2] = std::clamp((int)(img[neighborIndex + 2] + errorB * factor), 0, 255);
				}
			};*/

			/*spreadError(1, 0, 7.0 / 16.0);
			spreadError(-1, 1, 3.0 / 16.0);
			spreadError(0, 1, 5.0 / 16.0);
			spreadError(1, 1, 1.0 / 16.0);*/
		}
	}

	stbi_write_png(imagepath.c_str(), width, height, 3, ditheredImg.data(), width * 3);
	stbi_image_free(img);

	std::cout << "Dithered image saved as 'dithered_output.png'!\n";
}

} /* namespace ConsoleArt */
