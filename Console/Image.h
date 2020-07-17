#pragma once
class Image
{
private:
	//const char* INPUT_FILENAME = "ban hammer.png";
	char* fileName;
	unsigned char* imgData;
	int imgWidth;
	int imgHeight;
	struct ImgProps
	{
		char* name;
		unsigned char* data;
		const int width;
		const int height;
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

