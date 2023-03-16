//============================================================================
// Name        : ConsoleUtility
// Author      : Riyufuchi
// Created on  : 27.10.2021
// Last Edit   : 16.03.2023
//============================================================================

#include "ConsoleUtility.h"

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
		std::cin.get();
		if (!std::cin.fail())
			break;
		std::cerr << "Bad input, enter a number: ";
		std::cin.clear();
		std::cin.ignore(10,'\n');
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
	int result = getIntSafe(1, lenght) - 1;
	return result;
}

//args[x] = "arg| action";
void ConsoleUtility::createManual(std::string* args, int lenght)
{
	int lineLenght = 1;
	int lineTmp = 0;
	int columnWidth = 0;
	int xIndex = 0;
	for(int i = 0; i < lenght; i++)
	{
		lineTmp = args[i].length();
		while(args[i][xIndex] != '|')
			xIndex++;
		if(lineTmp > lineLenght)
			lineLenght = lineTmp;
		if(xIndex > columnWidth)
			columnWidth = xIndex;
		xIndex = 0;
	}
	char line[(lineTmp = lineLenght + columnWidth)];
	for(xIndex = 0; xIndex < lineTmp; xIndex++)
		line[xIndex] = '-';
	std::cout << line << "\n";
	for(int y = 0; y < lenght; y++)
	{
		xIndex = 0;
		while(args[y][xIndex] != '|')
		{
			std::cout << args[y][xIndex]; //printf("%c", args[y][x]);
			xIndex++;
		}
		for(lineTmp = xIndex; lineTmp < columnWidth; lineTmp++)
		{
			std::cout << " ";
		}
		if(args[y][xIndex] == '|')
			xIndex++;
		std::cout << " |";
		lineLenght = args[y].length();
		for(; xIndex < lineLenght; xIndex++)
			std::cout << args[y][xIndex];
		std::cout << " \n";
	}
	std::cout << line << "\n";
}

ConsoleUtility::~ConsoleUtility()
{
}
