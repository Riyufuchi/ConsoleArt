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
	c.ConstructConsole(800, 600, 12, 12);
	cin.get();
	//return 0;
}