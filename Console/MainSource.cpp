#include <stdio.h>
#include <iostream>
#include "Image.h"
//#include "MyConsole.h" //When compiling for unix-like systems, get rid of this line
#include "UnixConsole.h"

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 25.10.2021
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
	UnixConsole muc;
	Image img("/home/riyufuchi/Downloads/skynet2.bmp");
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
	std::cout << "Processing image..." << std::endl;
	img.getAsciiImg();
	for(int i = img.getBmpInfo().height - 1; i > -1; i--)
	{
		muc.writeText(img.apa[i]);
	}
	return 0;
}
