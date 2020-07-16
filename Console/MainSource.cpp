#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "MyConsole.h"

using namespace std;

/*
* Copyright Header
*
* Created On: 13.07.2020
* Last Edit: 14.07.2020
* Created By: Riyufuchi
*
*/


int main(int argc, char **argv)
{	
	cout << "Hello world, it's living time." << endl;
	cout << "Let's make some practise for the 'big game'." << endl;
	MyConsole c;
	c.test();
	c.setConsole();
	std::cout << "\x1b[32;1mHello\x1b[0m\n";
	std::cout << "\x1b[31;1mBye\x1b[0m\n";
	cin.get();
	//return 0;
}