#pragma once
class Image
{
private:
	//const char* INPUT_FILENAME = "ban hammer.png";
	char* fileName;
	int bitsPerPixel;
	int rowSize;
	int pixelArraySize;
	unsigned char bmpFileHeader[14];
	unsigned int pixelArrayOffset;
	unsigned char bmpInfoHeader[40];
	unsigned char* imgData;
	int imgWidth;
	int imgHeight;
	struct ImgProps
	{
		char* name;
		unsigned char* data;
	    int width;
		int height;
	};
	struct Pixel 
	{
		int red;
		int green;
		int blue;
		int rgb[];
	};
	void readBMP();
public:
	Image(char* filename);
	void imgToASCII();
	ImgProps getImgProperties();
	Pixel getPixel(int x, int y);
	~Image();
};

