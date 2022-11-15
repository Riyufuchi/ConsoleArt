#include "ConsoleUtility.h"

/* Copyright Header
* Created On: 27.10.2021
* Last Edit: 15.11.2022
* Created By: Riyufuchi
*/

ConsoleUtility::ConsoleUtility()
{
}

bool ConsoleUtility::yesNo(const char* text)
{
	std::string choice;
	std::cout << text;
	getline(std::cin, choice);
	//std::cin.ignore(); //clears buffer
	return (choice == "y" || choice == "Y" || choice == "");
}

bool ConsoleUtility::repeat()
{
	return yesNo("Again? [Y/n] ");
}

int ConsoleUtility::getIntSafe()
{
	int x = 0;
	while(true)
	{
		std::cin >> x;
		if (!std::cin.fail())
			break;
		//std::cin.clear();
		//std::cin.ignore(10000,'\n');
		std::cerr << "Bad input, enter a number: ";
	}
	return x;
}

int ConsoleUtility::getIntSafe(int min, int max)
{
	int x = 0;
	while(true)
	{
		x = getIntSafe();
		if(x >= min && x <= max)
			return x;
		else
			std::cout << "Enter a number in range " << min << " - " << max << ": ";
	}
}

void ConsoleUtility::header(std::string text)
{
	std::string line = "";
	int lenght = static_cast<int>(text.size());
	for(int i = 0; i < lenght; i++)
	{
		line += "-";
	}
	std::cout << line << "\n" << text << "\n" << line << std::endl;
}

int ConsoleUtility::basicMenu(int lenght, const char* menu[])
{
	for(int i = 0; i < lenght; i++)
	{
		printf("%d. %s \n", i + 1, menu[i]);
	}
	return (getIntSafe(1, lenght) - 1);
}

ConsoleUtility::~ConsoleUtility()
{
}
