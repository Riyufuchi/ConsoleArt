#include "Image.h"
#include <iostream>
#include <string>
#include <fstream>

void Image::readBMP()
{
	int i;
	/*
	//FILE* f = fopen(fileName, "rb");
	std::ifstream f(fileName);
	unsigned char info[54];
	// read the 54-byte header
	fread(info, sizeof(unsigned char), 54, (FILE*)f);
	// extract image height and width from header
	imgWidth = *(int*)&info[18];
	imgHeight = *(int*)&info[22];
	// allocate 3 bytes per pixel
	int size = 3 * imgWidth * imgHeight;
	unsigned char* data = new unsigned char[size];
	// read the rest of the data at once
	fread(data, sizeof(unsigned char), size, f);
	fclose(f);
	for (i = 0; i < size; i += 3)
	{
		// flip the order of every 3 bytes
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}
	*/
	//imgData = data;
}

Image::Pixel Image::getPixel(int x, int y)
{
	Pixel p;
	p.red = imgData[3 * (x * imgWidth + y)];
	p.green = imgData[3 * (x * imgWidth + y) + 1];
	p.blue = imgData[3 * (x * imgWidth + y) + 2];
	return p;
}

Image::Image(char* filename)
{
	fileName = filename;
	readBMP();
}

void Image::imgToASCII()
{
	std::string AsciiChars[] { "██", "##", "@@", "%%", "==", "++", "::", "--", "..", "  " };
	const ImgProps a = getImgProperties();
	std::string pictureInAscii[a.width][a.height];
	double podR = 0.2989;
	double podG = 0.5866;
	double podB = 0.1145;
	double brightness;
	int x = 0;
	int y = 0;
	int index = 0;
	while (true)
	{
		Pixel pix = getPixel(x, y);
		brightness = (pix.red * podR + pix.green * podG + pix.blue * podB);
		if (x != imgWidth - 1)
		{
			if (brightness > 25)
			{
				if (brightness > 50)
				{
					if (brightness > 75)
					{
						if (brightness > 100)
						{
							if (brightness > 125)
							{
								if (brightness > 150)
								{
									if (brightness > 175)
									{
										if (brightness > 200)
										{
											if (brightness > 225)
											{
												index = 9;
											}
											else
											{
												index = 8;
											}
										}
										else
										{
											index = 7;
										}
									}
									else
									{
										index = 6;
									}
								}
								else
								{
									index = 5;
								}
							}
							else
							{
								index = 4;
							}
						}
						else
						{
							index = 3;
						}
					}
					else
					{
						index = 2;
					}
				}
				else
				{
					index = 1;
				}
			}
			else
			{
				index = 0;
			}
			pictureInAscii = pictureInAscii + AsciiChars[index];
		}
		else
		{
			y++;
			if (y > imgHeight - 1)
			{

				break;
			}
			x = 0;
		}
		x++;
	}
}

Image::ImgProps Image::getImgProperties()
{
	ImgProps ip;
	ip.name = fileName;
	ip.data = imgData;
	ip.width = imgWidth;
	ip.height = imgHeight;
	return ip;
}

Image::~Image()
{
}
