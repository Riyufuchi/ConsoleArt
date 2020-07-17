#include <stdio.h>
#include <iostream>
#include <string>
#include "MyConsole.h"

using namespace std;

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 17.07.2020
* Created By: Riyufuchi
*
*/

int main(int argc, char **argv)
{	
	cout << "Hello world, it's living time." << endl;
	cout << "Let's make some practise for the 'big game'." << endl;
	MyConsole mc;
	mc.setBGColor(255, 105, 180);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	//mc.setTextColor(mc.D_BLUE);
	mc.test();
	//mc.start();
	cin.get();
	return 0;
}