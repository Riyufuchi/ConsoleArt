#include <stdio.h>
#include <iostream>
#include <string>
#include "Image.h"
#include "ConsoleUtility.h"
//#include "MyConsole.h" //When compiling for unix-like systems, get rid of this line
#include "UnixConsole.h"

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 27.10.2021
* Created By: Riyufuchi
*
*/

Image loadImage()
{
	std::cout << "Image name, without type (only .bmp images)" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	imgName.append(".bmp");
	std::string path = "/home/riyufuchi/Downloads/";
	Image img((path.append(imgName)).c_str());
	return img;
}

void linuxVersion(Image img)
{
	if(img.getFilename() != std::string("NULL"))
	{
		UnixConsole uc;
		std::cout << "Press Enter to continue..." << std::endl;
		std::cin.get();
		std::cin.get();
		std::cout << "Processing image..." << std::endl;
		img.imgToArray(); //Convert image to chars and save it in array
		for(int i = 0; i < img.getBmpInfo().height; i++) //Outputing converted image
		{
			uc.writeText(img.apa[i]);
		}
		img.convertToASCII(); //Converts image and outputs it line by line
	}
}

void forWindows(Image img)
{
	/*
	if(img.filename != NULL)
	{
		MyConsole mc;
		mc.setTextColor(mc.HOT_PINK);
		//Image img("D:/Files/Programming/C++ Visual Studio/ConsoleArt/x64/Debug/img.bmp");
		cout << "Press Enter to continue..." << endl;
		cin.get();
		std::cin.get();
		cout << "Processing image..." << endl;
		img.writeImgToASCII();
	}
	*/
}

int main(int argc, char **argv)
{
	//cout << "Hello world, it's living time." << endl;
	//cout << "Let's make some practise for the 'big game'." << endl;
	ConsoleUtility cu;
	cu.header("Image to ASCII converter");
	do
	{
		linuxVersion(loadImage());
	}while(cu.repeat());
	return 0;
}
