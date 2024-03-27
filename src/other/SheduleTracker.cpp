//==============================================================================
// File       : SheduleTracker.cpp
// Author     : riyufuchi
// Created on : Mar 26, 2024
// Last edit  : Mar 26, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "SheduleTracker.h"

namespace Other
{
SheduleTracker::SheduleTracker(ConsoleLib::IConsole* console) : console(console)
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
bool SheduleTracker::readFile()
{
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
	return true;
}
void SheduleTracker::calculateAvgTime()
{
	if (!readFile())
		return;
	long minutes = 0;
	for (DataUtility::TimeStamp& timeStamp : times)
	{
		minutes += DataUtility::TimeUtils::convertToMinutes(timeStamp);
	}
	minutes /= 60;
	double avgHour = (double)minutes / times.size();
	console->out("Average time is: ");
	console->defaultTextColor();
	std::cout << avgHour << "\n";
	console->resetTextColor();
}
} /* namespace ConsoleArt */
