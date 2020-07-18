#include "Image.h"

void Image::readBMP()
{
	using namespace std;
	ifstream inf(fileName, ios::in);
	if (inf) 
	{
		inf.read((char*)&file_header, sizeof(file_header));
		if (file_header.file_type != 0x4D42)
		{
			throw runtime_error("Error: Unecognized fromtat.");
		}
		inf.read((char*)&bmp_info_header, sizeof(bmp_info_header));
		if (bmp_info_header.bit_count == 32)
		{
			if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader)))
			{
				inf.read((char*)&bmp_color_header, sizeof(bmp_color_header));
				check_color_header(bmp_color_header);
			}
			else
			{
				cerr << "Warning! The file \"" << fileName << "\" does not seem to contain bit mask information\n";
				throw std::runtime_error("Error! Unrecognized file format.");
			}
		}
		inf.seekg(file_header.offset_data, inf.beg);
		if (bmp_info_header.bit_count == 32)
		{
			bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
			file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
		}
		else
		{
			bmp_info_header.size = sizeof(BMPInfoHeader);
			file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
		}
		file_header.file_size = file_header.offset_data;
		if (bmp_info_header.height < 0)
		{
			throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
		}
		imgData.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);
		if (bmp_info_header.width % 4 == 0)
		{
			inf.read((char*)imgData.data(), imgData.size());
			file_header.file_size += imgData.size();
		}
		else
		{
			row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
			uint32_t new_stride = make_stride_aligned(4);
			vector<uint8_t> padding_row(new_stride - row_stride);
			for (int y = 0; y < bmp_info_header.height; ++y)
			{
				inf.read((char*)(imgData.data() + row_stride * y), row_stride);
				inf.read((char*)padding_row.data(), padding_row.size());
			}
			file_header.file_size += imgData.size() + bmp_info_header.height * padding_row.size();
		}
		cout << "Img loaded: " << fileName << "\n";
		//imgPixels = (int)imgData.data();
	}
	else
	{
		cerr << "Unable to open file: " << fileName << "\n";
	}
	/*
	int a;
	for (int i = 0; i < bmp_info_header.height * bmp_info_header.width; i++)
	{
		inf >> a;
		imgData[i] = a;
	}
	*/
	//Old code
	/*
	//unsigned char m_bmpFileHeader[14];file_header.file_size = file_header.offset_data;
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
	/*
	unsigned int * array_offset_ptr = (unsigned int *)(bmpFileHeader + 10);
	pixelArrayOffset = *array_offset_ptr;
	if (bmpFileHeader[11] != 0 || bmpFileHeader[12] != 0 || bmpFileHeader[13] != 0) 
	{
		std::cerr << "You probably need to fix something. (" << __LINE__ << ")\n";
	}
	//unsigned char m_bmpInfoHeader[40];
	for (int i = 0; i < 40; i++) 
	{
		inf >> hex >> a;
		bmpInfoHeader[i] = a;
	}
	/*
	int * width_ptr = (int*)(bmpInfoHeader + 4);
	int * height_ptr = (int*)(bmpInfoHeader + 8);
	imgWidth = *width_ptr;
	imgHeight = *height_ptr;
	*/
	/*
	imgWidth = 100;
	imgHeight = 100;
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
		cerr << "Comment out offending lines to continue anyways. line: " << __LINE__ << "\n";
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

void Image::check_color_header(BMPColorHeader & bmp_color_header)
{
	BMPColorHeader expected_color_header;
	if (expected_color_header.red_mask != bmp_color_header.red_mask || expected_color_header.blue_mask != bmp_color_header.blue_mask || expected_color_header.green_mask != bmp_color_header.green_mask || expected_color_header.alpha_mask != bmp_color_header.alpha_mask)
	{
		throw std::runtime_error("Unexpected color mask format! The program expects the pixel data to be in the BGRA format");
	}
	if (expected_color_header.color_space_type != bmp_color_header.color_space_type)
	{
		throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
	}
}

uint32_t Image::make_stride_aligned(uint32_t align_stride)
{
	uint32_t new_stride = row_stride;
	while (new_stride % align_stride != 0)
	{
		new_stride++;
	}
	return new_stride;
}

Image::Pixel Image::getPixel(int x, int y)
{
	Pixel p;
	/*
	p.red = imgData[3 * (x * imgWidth + y)];
	p.green = imgData[3 * (x * imgWidth + y) + 1];
	p.blue = imgData[3 * (x * imgWidth + y) + 2];
	*/
	uint32_t channels = bmp_info_header.bit_count / 8;
	p.red = (imgData[channels * (y * bmp_info_header.width + x) + 2]);
	if (p.red < 0)
	{
		p.red *= -1;
	}
	p.green = imgData[channels * (y * bmp_info_header.width + x) + 1];
	if (p.green < 0)
	{
		p.green *= -1;
	}
	p.blue = imgData[channels * (y * bmp_info_header.width + x) + 0];
	if (p.blue < 0)
	{
		p.blue *= -1;
	}
	return p;
}

int Image::getRed(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	if((int)imgData[channels * (y * bmp_info_header.width + x) + 2] < 0)
	{
		return imgData[channels * (y * bmp_info_header.width + x) + 2] * -1;
	}
	return (int)imgData[channels * (y * bmp_info_header.width + x) + 2];
}
int Image::getGreen(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	return (int)((imgData[channels * (y * bmp_info_header.width + x) + 1])-48);
}
int Image::getBlue(int x, int y)
{
	uint32_t channels = bmp_info_header.bit_count / 8;
	return (int)((imgData[channels * (y * bmp_info_header.width + x) + 0])-48);
}

Image::Image(const char* filename)
{
	fileName = filename;
	readBMP();
}

Image::AsciiPicture Image::imgToASCII()
{
	std::string AsciiChars[] { "FF", "##", "@@", "%%", "==", "++", "::", "--", "..", "  " };
	std::string line = "";
	const int h = bmp_info_header.height;
	std::string* a = new std::string[h];
	double podR = 0.2989;
	double podG = 0.5866;
	double podB = 0.1145;
	int brightness;
	int x = 0;
	int y = 0;
	int index = 0;
	while (true)
	{
		Pixel pix = getPixel(x, y);
		brightness = (pix.red * podR + pix.green * podG + pix.blue * podB);
		/*std::cout << "X: " << x << "\n";
		std::cout << "Y: " << y << "\n";
		std::cout << "Red: " << getRed(x, y) << "\n";
		std::cout << "Green: " << getGreen(x, y) << "\n";
		std::cout << "Blue: " << getBlue(x, y) << "\n";
		*/
		if (x != bmp_info_header.width - 1)
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
			a[y] = line + "\n";
			std::cout << line << "\n";
			line = "";
			y++;
			if (y > bmp_info_header.height - 1)
			{
				break;
			}
			x = 0;
		}
		x++;
		//std::cout << "X: " << x << "\n";
	}
	AsciiPicture ap;
	ap.apa = a;
	return ap;
}

Image::ImgProps Image::getImgProperties()
{
	ImgProps ip;
	//ip.name = fileName;
	//ip.data = imgData;
	ip.width = imgWidth;
	ip.height = imgHeight;
	return ip;
}

Image::~Image()
{
}
