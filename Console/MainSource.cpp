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

int main(int argc, char **argv)
{	
	cout << "Hello world, it's living time." << endl;
	cout << "Let's make some practise for the 'big game'." << endl;
	MyConsole mc;
	mc.setTextColor(mc.HOT_PINK);
	//mc.test();
	Image img("img.bmp");
	std::string* a = img.imgToASCII().apa;
	for (int i = 0; i < 100; i++)
	{
		cout << a[i] + "\n";
	}
	cin.get();
	return 0;
}