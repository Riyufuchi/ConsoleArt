//==============================================================================
// File       : SheduleTracker.cpp
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : Apr 09, 2024
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "SheduleTracker.h"

namespace Other
{
SheduleTracker::SheduleTracker(ConsoleLib::IConsole* console) : console(console), fileLoaded(false)
{
	if (console == nullptr)
	{
		this->console = console = new ConsoleLib::DefaultConsole();
		console->err("Pointer to console controller was NULL!\a\n");
	}
}
SheduleTracker::~SheduleTracker()
{
}
void SheduleTracker::menu()
{
	const char* menuItems[] = { "Add time", "Calculate avg time", "Exit" };
	std::string line;
	readFile();
	do
	{
		console->defaultTextColor();
		switch (ConsoleLib::ConsoleUtils::basicMenu(sizeof(menuItems)/sizeof(*menuItems), menuItems))
		{
			case 0:
				console->out("Enter: HOURS;MINUTES\n");
				std::getline(std::cin, line);
				writeFile(line, filename);
			break;
			case 1:
				if (!readFile())
					break;
				calculateAvgTime();
			break;
			case 2:
				line = "end";
			break;
		}
	} while (line != "end");
	console->out("Press enter to exit...");
	std::cin.get();
}
bool SheduleTracker::writeFile(const std::string& line, const std::string& filename)
{
	std::ofstream file(filename, std::ios::app); // Open file in append mode
	if (!file.is_open())
	{
		std::cerr << "Error: Unable to open file for appending.\n";
		return false;
	}
	file << line << std::endl; // Append line to file
	std::cout << "Line appended to file successfully.\n";
	times.emplace_back(DataUtility::TimeStamp{0, std::stol(line.substr(0, line.find(';'))), std::stol(line.substr(line.find(';') + 1, line.length()))});
	return true;
}
bool SheduleTracker::readFile()
{
	if (fileLoaded)
		return true;
	times.clear();
	std::ifstream file(filename);
	if (!file.is_open())
	{
		console->err("Error: Unable to open file \"stat.csv\"\n");
		return false;
	}
	std::string line, token;
	DataUtility::TimeStamp timeStamp;
	const int NUM_OF_ATTRIBUTES = 2;
	int x = 0;
	std::istringstream iss("");
	while (std::getline(file, line))
	{
		iss = std::istringstream(line);
		for (x = 0; x < NUM_OF_ATTRIBUTES; x++)
		{
			if (std::getline(iss, token, ';')) // Split the line using ';' as delimiter
			{
				switch (x)
				{
					case 0: timeStamp.hours = std::stol(token); break;
					case 1: timeStamp.minutes = std::stol(token); break;
				}
			}
			else
			{
				console->err("Error: Invalid file format!\n");
				return false;
			}
		}
		times.push_back(timeStamp);
	}
	file.close();
	console->out("Success: File loaded!\n");
	return fileLoaded = true;
}
void SheduleTracker::calculateAvgTime()
{
	long double minutes = 0;
	int week = 1;
	int days = 0;
	for (DataUtility::TimeStamp& timeStamp : times)
	{
		minutes += DataUtility::TimeUtils::convertToMinutes(timeStamp);
		days++;
		if (days % 7 == 0)
		{
			std::cout << "Week " << week << ": " << (minutes / 60) / days << "\n";
			week++;
			days = 0;
			minutes = 0;
		}
	}
	if (days != 0)
		std::cout << "Week " << week << ": " << (minutes / 60) / days << "\n";
}
} /* namespace ConsoleArt */
