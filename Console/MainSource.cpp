#include <stdio.h>
#include <iostream>
#include "Image.h"
//#include "MyConsole.h" //When compiling for unix-like systems, get rid of this line
#include "UnixConsole.h"

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 26.10.2021
* Created By: Riyufuchi
*
*/

int main(int argc, char **argv)
{
	//cout << "Hello world, it's living time." << endl;
	//cout << "Let's make some practise for the 'big game'." << endl;
	//For Windows
	/*
	MyConsole mc;
	mc.setTextColor(mc.HOT_PINK);
	Image img("D:/Files/Programming/C++ Visual Studio/ConsoleArt/x64/Debug/img.bmp");
	cout << "Press Enter to continue..." << endl;
	cin.get();
	cout << "Processing image..." << endl;
	img.writeImgToASCII();
	*/
	//For Unix-like systems
	UnixConsole uc;
	Image img("/home/riyufuchi/Downloads/Wild_Card.bmp");
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;

	img.imgToArray(); //Convert image to chars and save it in array
	for(int i = 0; i < img.getBmpInfo().height; i++) //Outputing converted image
	{
		uc.writeText(img.apa[i]);
	}

	img.convertToASCII(); //Converts image and outputs it line by line

	return 0;
}
