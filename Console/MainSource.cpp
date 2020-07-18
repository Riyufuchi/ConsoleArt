#include <stdio.h>
#include <iostream>
#include "Image.h"
#include "MyConsole.h"

using namespace std;

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 18.07.2020
* Created By: Riyufuchi
*
*/

int wmain(int argc, char **argv)
{	
	cout << "Hello world, it's living time." << endl;
	cout << "Let's make some practise for the 'big game'." << endl;
	MyConsole mc;
	mc.setTextColor(mc.HOT_PINK);
	Image img("D:/Files/Programming/C++ Visual Studio/ConsoleArt/x64/Debug/img.bmp");
	cin.get();
	std::string* a = img.imgToASCII().apa;
	cin.get();
	return 0;
}