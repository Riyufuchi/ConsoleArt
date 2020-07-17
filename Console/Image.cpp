#include "Image.h"
#include <iostream>
#include <string>
#include <fstream>

void Image::readBMP()
{
	using namespace std;
	ifstream inf(fileName);
	if (!inf) 
	{
		cerr << "Unable to open file: " << fileName << "\n";
	}
	//unsigned char m_bmpFileHeader[14];
	unsigned char a;
	for (int i = 0; i < 14; i++) 
	{
		inf >> hex >> a;
		bmpFileHeader[i] = a;
	}
	if (bmpFileHeader[0] != 'B' || bmpFileHeader[1] != 'M') 
	{
		cerr << "Your info header might be different!\nIt should start with 'BM'.\n";
	}
	/*
		THE FOLLOWING LINE ONLY WORKS IF THE OFFSET IS 1 BYTE!!!!! (it can be 4 bytes max)
		That should be fixed now.
		old line was
		m_pixelArrayOffset = m_bmpFileHeader[10];
	*/
	unsigned int * array_offset_ptr = (unsigned int *)(bmpFileHeader + 10);
	pixelArrayOffset = *array_offset_ptr;
	if (bmpFileHeader[11] != 0 || bmpFileHeader[12] != 0 || bmpFileHeader[13] != 0) 
	{
		std::cerr << "You probably need to fix something. bmp.h(" << __LINE__ << ")\n";
	}
	//unsigned char m_bmpInfoHeader[40];
	for (int i = 0; i < 40; i++) 
	{
		inf >> hex >> a;
		bmpInfoHeader[i] = a;
	}
	int * width_ptr = (int*)(bmpInfoHeader + 4);
	int * height_ptr = (int*)(bmpInfoHeader + 8);
	imgWidth = *width_ptr;
	imgHeight = *height_ptr;
	printf("W: %i, H: %i", imgWidth, imgHeight);

	bitsPerPixel =bmpInfoHeader[14];
	if (bitsPerPixel != 24) 
	{
		cerr << "This program is for 24bpp files. Your bmp is not that\n";
	}
	int compressionMethod =bmpInfoHeader[16];
	if (compressionMethod != 0) 
	{
		cerr << "There's some compression stuff going on that we might not be able to deal with.\n";
		cerr << "Comment out offending lines to continue anyways. bpm.h line: " << __LINE__ << "\n";
	}
	rowSize = int(floor((bitsPerPixel*imgWidth + 31.) / 32)) * 4;
	pixelArraySize = rowSize * abs(imgHeight);
	imgData = new unsigned char[pixelArraySize];
	inf.seekg(pixelArrayOffset, ios::beg);
	for (int i = 0; i < pixelArraySize; i++) 
	{
		inf >> hex >> a;
		imgData[i] = a;
	}
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
	/*
	p.red = imgData[3 * (x * imgWidth + y)];
	p.green = imgData[3 * (x * imgWidth + y) + 1];
	p.blue = imgData[3 * (x * imgWidth + y) + 2];
	*/
	p.red = (unsigned int)(imgData[rowSize*y + 3 * x + 2]);
	p.green = (unsigned int)(imgData[rowSize*y + 3 * x + 1]);
	p.blue = (unsigned int)(imgData[rowSize*y + 3 * x + 0]);
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
	std::string line = "";
	const int h = imgHeight;
	std::string* a = new std::string[h];
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
			line = line + AsciiChars[index];
		}
		else
		{
			a[y] = line;
			line = "";
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
