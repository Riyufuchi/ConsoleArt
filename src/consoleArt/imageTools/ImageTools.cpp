//==============================================================================
// File       : ImageTools.cpp
// Author     : riyufuchi
// Created on : Dec 1, 2023
// Last edit  : May 31, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageTools.h"

namespace ImageUtils
{
ImageTools::ImageTools()
{
}
ImageTools::~ImageTools()
{
}
std::unique_ptr<unsigned char[]> ImageTools::convertPlanarPCXToInterleaved(const Images::ImagePCX& image)
{
	const Images::ImagePCX::PCXHeader &header = image.getHeader();
	int totalPixels = image.getWidth() * image.getHeight();

	std::unique_ptr planarData = image.getImageData();
	unsigned char* interleavedData = new unsigned char[totalPixels * header.numOfColorPlanes]; // Supports RGB or RGBA

	int pixelIndex = 0;
	int RGBpos = 0;
	for (int y = 0; y < image.getHeight(); y++)
	{
		for (int x = 0; x < image.getWidth(); x++)
		{
			pixelIndex = (y * header.numOfColorPlanes * header.bytesPerLine) + x;
			RGBpos = (y * image.getWidth() + x) * 3;
			interleavedData[RGBpos] = planarData[pixelIndex];
			interleavedData[RGBpos + 1] = planarData[header.bytesPerLine + pixelIndex];
			interleavedData[RGBpos + 2] = planarData[(header.bytesPerLine * 2) + pixelIndex];
		}
	}
	return std::unique_ptr<unsigned char []>(interleavedData);
}
unsigned char* ImageTools::normalizeToRGBA(const Images::Image& image, Images::ImageInfo& imageInfo)
{
	int CHANNELS = imageInfo.bits / 8;
	if (CHANNELS < 3)
	{
		CHANNELS = 3;
		imageInfo.bits = 24;
	}
	unsigned char* imageDat = new unsigned char[imageInfo.width * imageInfo.height * CHANNELS];
	Images::Pixel pixel;
	int xyCord = 0;
	if (image.isInverted())
		for(int y = 0; y < imageInfo.height; y++)
		{
			for (int x = 0; x < imageInfo.width; x++)
			{
				pixel = image.getPixel(x, y);
				xyCord = ((imageInfo.height - 1 - y) * imageInfo.width + x) * CHANNELS; // Fix: Flip row position
				imageDat[xyCord] = pixel.red;
				imageDat[xyCord + 1] = pixel.green;
				imageDat[xyCord + 2] = pixel.blue;
				if (CHANNELS == 4)
					imageDat[xyCord + 3] = pixel.alpha;
			}
		}
	else
		for(int y = 0; y < imageInfo.height; y++)
		{
			for (int x = 0; x < imageInfo.width; x++)
			{
				pixel = image.getPixel(x, y);
				xyCord = (y * imageInfo.width + x) * CHANNELS;
				imageDat[xyCord] = pixel.red;
				imageDat[xyCord + 1] = pixel.green;
				imageDat[xyCord + 2] = pixel.blue;
				if (CHANNELS == 4)
					imageDat[xyCord + 3] = pixel.alpha;
			}
		}
	return imageDat;
}
void ImageTools::addToImageName(Images::Image& image,const std::string addStr)
{
	if (!image)
		return;
	image.rename(image.getFilename().substr(0, image.getFilename().find(".")) + addStr);
}
int ImageTools::compareImages(const Images::Image& image1, const Images::Image& image2)
{
	if (image1 == image2)
		return 0;
	else if (image1 > image2)
		return 1;
	else if (image1 < image2)
		return -1;
	else
		return -2;
}
void ImageTools::nearestNeighbor(const Images::Image& originalImage, Images::Image& scaledImage)
{
	const Images::ImageInfo& canvasInfo = originalImage.getImageInfo(); // Old values
	const Images::ImageInfo& scaledInfo = scaledImage.getImageInfo(); // New values

	const double scaleX = static_cast<double>(canvasInfo.width) / scaledInfo.width;
	const double scaleY = static_cast<double>(canvasInfo.height) / scaledInfo.height;

	int srcX = 0;
	int srcY = 0;

	for (int y = 0; y < scaledInfo.height; y++)
	{
		for (int x = 0; x < scaledInfo.width; x++)
		{
			// Clamp to prevent out-of-bounds access
			srcX = std::min(static_cast<int>(x * scaleX), canvasInfo.width - 1);
			srcY = std::min(static_cast<int>(y * scaleY), canvasInfo.height - 1);

			scaledImage.setPixel(x, y, originalImage.getPixel(srcX, srcY));
		}
	}
}

bool ImageTools::signatureToImage(Images::Image& canvasImage, const Images::Image& signature)
{
	const Images::ImageInfo& canvasInfo = canvasImage.getImageInfo();
	const Images::ImageInfo& signatureInfo = signature.getImageInfo();

	const double SCALE_FACTOR = 0.25; // 25% of the larger side
	int targetWidth, targetHeight;

	// Scale based on the width or height, whichever is larger
	if (canvasInfo.width >= canvasInfo.height)
	{
		targetWidth = static_cast<int>(canvasInfo.width * SCALE_FACTOR);
		targetHeight = static_cast<int>(signatureInfo.height * (targetWidth / static_cast<double>(signatureInfo.width)));
	}
	else
	{
		targetHeight = static_cast<int>(canvasInfo.height * SCALE_FACTOR);
		targetWidth = static_cast<int>(signatureInfo.width * (targetHeight / static_cast<double>(signatureInfo.height)));
	}

	Images::ImagePNG resizedSignature(signature.getFilepath(), targetWidth, targetHeight, 4);
	nearestNeighbor(signature, resizedSignature);

	const int X = canvasInfo.width - targetWidth;
	const int Y = canvasInfo.height - targetHeight;

	int x = 0;
	int x1 = 0;

	Images::Pixel pixel;
	Images::Pixel pixelCanvas;
	Images::Pixel pixelBlend;

	if (canvasImage.isInverted())
	{
		for (int y = 0, y1 = targetHeight; y1 >= 0; y++, y1--)
		{
			for (x = X, x1 = 0; x < canvasInfo.width; x++, x1++)
			{
				pixel = resizedSignature.getPixel(x1, y1);
				switch (pixel.alpha)
				{
					case 0: continue;
					case 255: canvasImage.setPixel(x, y, pixel); break;
					default:
						pixelCanvas = canvasImage.getPixel(x, y);
						pixelBlend.red = (pixel.red * pixel.alpha + pixelCanvas.red * (255 - pixel.alpha)) / 255;
						pixelBlend.green = (pixel.green * pixel.alpha + pixelCanvas.green * (255 - pixel.alpha)) / 255;
						pixelBlend.blue = (pixel.blue * pixel.alpha + pixelCanvas.blue * (255 - pixel.alpha)) / 255;
						//pixelBlend.alpha = 255; // Result is fully opaquexel = resizedSignature.getPixel(x1, y1);
						canvasImage.setPixel(x, y, pixelBlend);
					break;
				}
			}
		}
	}
	else
	{
		for (int y = Y, y1 = 0; y < canvasInfo.height; y++, y1++)
		{
			for (x = X, x1 = 0; x < canvasInfo.width; x++, x1++)
			{
				pixel = resizedSignature.getPixel(x1, y1);
				switch (pixel.alpha)
				{
					case 0: continue;
					case 255:
						canvasImage.setPixel(x, y, pixel);
					break;
					default:
						pixelCanvas = canvasImage.getPixel(x, y);
						pixelBlend.red = (pixel.red * pixel.alpha + pixelCanvas.red * (255 - pixel.alpha)) / 255;
						pixelBlend.green = (pixel.green * pixel.alpha + pixelCanvas.green * (255 - pixel.alpha)) / 255;
						pixelBlend.blue = (pixel.blue * pixel.alpha + pixelCanvas.blue * (255 - pixel.alpha)) / 255;
						//pixelBlend.alpha = 255; // Result is fully opaquexel = resizedSignature.getPixel(x1, y1);
						canvasImage.setPixel(x, y, pixelBlend);
					break;
				}
			}
		}
	}

	addToImageName(canvasImage, "-signed");
	return canvasImage.saveImage();
}
} /* namespace ImageUtils */
