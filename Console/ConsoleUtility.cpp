#include "ConsoleUtility.h"

/* Copyright Header
* Created On: 27.10.2021
* Last Edit: 24.03.2022
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

int ConsoleUtility::getIntSafe()
{
   int x = 0;
   while(true)
   {
		 std::cin >> x;
		 if (!std::cin.fail())
		 		break;
		 std::cin.clear();
		 std::cin.ignore(10000,'\n');
		 std::cout << "Bad input!\nEnter a number: ";
    }
		return x;
 }

 int ConsoleUtility::getIntSafe(int min, int max)
 {
    int x = 0;
    while(true)
    {
 		 std::cin >> x;
 		 if (!std::cin.fail())
		 {
			 if(x >= min && x <= max)
					break;
		 }
 		 std::cin.clear();
 		 std::cin.ignore(10000,'\n');
 		 std::cout << "Bad entry!\nEnter a number (" << min << " - " << max << "): ";
     }
 		return x;
  }

void ConsoleUtility::header(std::string text)
{
	std::string line = "";
	int lenght = (int) text.size();
	for(int i = 0; i < lenght; i++)
	{
		line += "-";
	}
	std::cout << line << "\n" << text << "\n" << line << std::endl;
}

ConsoleUtility::~ConsoleUtility()
{
}
