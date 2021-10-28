#include "ConsoleUtility.h"

/* Copyright Header
* Created On: 27.10.2021
* Last Edit: 28.10.2021
* Created By: Riyufuchi
*/

ConsoleUtility::ConsoleUtility()
{
}

bool ConsoleUtility::repeat()
{
	std::string choice;
	std::cout << "Again? [Y/n]: ";
	getline(std::cin, choice);
	if(choice == "y" || choice == "Y" || choice == "")
	{
		return true;
	}
	return false;
}

void ConsoleUtility::header(std::string text)
{
	std::string line = "";
	for(int i = 0; i < text.size(); i++)
	{
		line += "-";
	}
	std::cout << line << "\n" << text << "\n" << line << std::endl;
}

ConsoleUtility::~ConsoleUtility()
{
}
