#include <stdio.h>
#include <iostream>
#include "Image.h"
#include "MyConsole.h"
#include "MyUnixConsole.h"

using namespace std;

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 20.07.2020
* Created By: Riyufuchi
*
*/

int main(int argc, char **argv)
{
	cout << "Hello world, it's living time." << endl;
	cout << "Let's make some practise for the 'big game'." << endl;
	MyConsole mc;
	mc.setTextColor(mc.HOT_PINK);
	Image img("D:/Files/Programming/C++ Visual Studio/ConsoleArt/x64/Debug/img.bmp");
	cout << "Press Enter to continue..." << endl;
	cin.get();
	cout << "Processing image..." << endl;
	//img.writeImgToASCII();
	//For Unix-like systems
	MyUnixConsole muc;
	img.getAsciiImg();
	for(int i = 0; i < 300; i++)
	{
		muc.writeText(img.apa[i]);
	}
	muc.writeText("Finished");
	//muc.writeText("a");
	cin.get();
	return 0;
}