#include <stdio.h>
#include <iostream>
#include <string>
#include "Image.h"
#include "ConsoleUtility.h"
//#include "MyConsole.h" //When compiling for unix-like systems, get rid of these files
#include "UnixConsole.h"

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 08.11.2022
* Created By: Riyufuchi
*
*/
Image loadImage()
{
	std::cout << "Image name without file extension (only .bmp images):" << std::endl;
	std::string imgName;
	std::cin >> imgName;
	imgName.append(".bmp");
	std::string path = "/home/riyufuchi/Pictures/toAscii/";
	Image img((path.append(imgName)).c_str());
	return img;
}
/*
 * Create a simple menu
 */
int charSetMenu()
{
	const char* menuItems[] = { "BASIC - █#@%=+:-. ", "PRECISE", "DEATAILED", "DETAILED_INVERTED - .-:*+=x%@#░▒▓█" };
	const int lenght = sizeof(menuItems)/sizeof(menuItems[0]);
	for(int i = 0; i < lenght; i++)
	{
		printf("%d. %s \n", i + 1, menuItems[i]);
	}
	return (ConsoleUtility::getIntSafe(1, lenght) - 1);
}

void linuxVersion(Image img)
{
	if(img.getFilename() != std::string("NULL"))
	{
		UnixConsole uc;
		img.setCharSet(charSetMenu());
		std::cout << "Press Enter to continue..." << std::endl;
		std::cin.get();
		std::cin.get();
		std::cout << "Processing image..." << std::endl;
		img.convertToASCII(); //Converts image to chars and save it in array
		if (ConsoleUtility::yesNo("Custom color [Y/n]: "))
		{
			std::cout << "Red: ";
			int red = ConsoleUtility::getIntSafe(0, 255);
			std::cout << "Green: ";
			int green = ConsoleUtility::getIntSafe(0, 255);
			std::cout << "Blue: ";
			int blue = ConsoleUtility::getIntSafe(0, 255);
			uc.setMainTextColor(uc.setColor(red, green, blue));
		}
		//Explicit outputting of converted image
		const int height = img.getBmpInfo().height;
		for(int i = 0; i < height; i++)
		{
			uc.writeText(img.getLine(i));
		}
		//Implicit:
		//img.outputAsciiImage();
	}
	std::cin.get(); //Catch enter character - if not, user will press enter anyway
}

/*
void forWindows(Image img)
{
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
}
*/

int main(int argc, char **argv)
{
	ConsoleUtility::header("Image to ASCII converter");
	do
	{
		linuxVersion(loadImage());
	}while(ConsoleUtility::repeat());
	return 0;
}
