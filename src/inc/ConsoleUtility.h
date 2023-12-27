//============================================================================
// Name        : ConsoleUtility
// Author      : Riyufuchi
// Created on  : 27.10.2021
// Last Edit   : 19.12.2023
//============================================================================

#ifndef _CONSOLEUTILITY_H_
#define _CONSOLEUTILITY_H_

#include <string.h>
#include <iostream>
#include <filesystem>
#include "IConsole.hpp"

/**
 * This class helps with console interactions
 */
namespace ConsoleUtils
{
// TODO: Add methods that support colored text
class ConsoleUtility
{
private:
public:
	ConsoleUtility();
	static bool repeat();
	static bool yesNo(const char* text);
	static int getIntSafe();
	static int getIntSafe(int min, int max);
	template <typename T> static T getInput()
	{
		T x;
		while(true)
		{
			std::cin >> x;
			std::cin.get();
			if (!std::cin.fail())
				break;
			std::cerr << "Bad input.\n";
			std::cout << "Input again: ";
			std::cin.clear();
			std::cin.ignore(10,'\n');
		}
		return x;
	}
	static void header(std::string);
	static void header(std::string text, IConsole& console, Color textColor);
	static int basicMenu(int lenght, const char* menu[]);
	static void createManual(std::string* args, int lenght);
	static void listFilesInFolder(std::string workspacePath);
	~ConsoleUtility();
};
}
#endif
