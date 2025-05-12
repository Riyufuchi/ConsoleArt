//==============================================================================
// File       : SheduleTracker.cpp
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : May 07, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ScheduleTracker.h"

namespace Other
{
ScheduleTracker::ScheduleTracker(ConsoleLib::IConsole& console) : console(console), fileLoaded(false), lastEvent(ButtonEvent::NONE), menu(console, menuTexts, [&](){ printHeader(); })
{
	menuTexts.emplace_back("Add time");
	menuTexts.emplace_back("Calculate average time");
	menuTexts.emplace_back("Exit");
}
ScheduleTracker::~ScheduleTracker()
{
}
void ScheduleTracker::run()
{
	readFile();
	do
	{
		console.enableCustomFG();
		switch (menu.runMenuLoop())
		{
			case 0: lastEvent = ButtonEvent::ADD_TIMESTAMP; break;
			case 1: lastEvent = ButtonEvent::DISPLAY_DATA; break;
			case 2: lastEvent = ButtonEvent::EXIT; break;
		}
	} while (lastEvent != EXIT);
	console.out("Press enter to exit...");
	std::cin.get();
}
bool ScheduleTracker::writeFile(const std::string& line, const std::string& filename)
{
	std::ofstream file(filename, std::ios::app); // Open file in append mode
	if (!file.is_open())
	{
		std::cerr << "Error: Unable to open file for appending.\n";
		return false;
	}
	std::string date = ConsoleLib::TimeUtils::dateToString(ConsoleLib::TimeUtils::todaysDate());
	file << line << ";" << date << std::endl; // Append line to file
	std::cout << "Line appended to file successfully.\n";
	ConsoleLib::TimeStamp data;
	std::string strNum = line.substr(0, line.find(';'));
	convertToLong(data.hours, strNum);
	convertToLong(data.minutes, strNum = line.substr(line.find(';') + 1, line.length()));
	times.emplace_back(data);
	dates.emplace_back(date);
	return true;
}
void ScheduleTracker::convertToLong(long& destination, std::string& number)
{
	try
	{
		destination = std::stol(number);
		return;
	}
	catch (const std::invalid_argument& e)
	{
		console.err("Invalid argument: " + number.append("\n"));
	}
	catch (const std::out_of_range& e)
	{
		console.err("Out of range: " + number.append("\n"));
	}
	destination = 0;
}

bool ScheduleTracker::readFile()
{
	if (fileLoaded)
		return true;
	times.clear();
	std::ifstream file(filename);
	if (!file.is_open())
	{
		console.err("Error: Unable to open file \"stat.csv\"\n");
		fileSelect();
		return false;
	}
	std::string line, token;
	ConsoleLib::TimeStamp timeStamp;
	const int NUM_OF_ATTRIBUTES = 3;
	int x = 0;
	std::istringstream iss;
	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue;
		iss = std::istringstream(line);
		for (x = 0; x < NUM_OF_ATTRIBUTES; x++)
		{
			if (std::getline(iss, token, ';')) // Split the line using ';' as delimiter
			{
				switch (x)
				{
					case 0: convertToLong(timeStamp.hours, token); break;
					case 1: convertToLong(timeStamp.minutes, token); break;
					case 2: dates.emplace_back(token); break;
				}
			}
			else
			{
				console.err("Error: Invalid file format!\n");
				return false;
			}
		}
		times.push_back(timeStamp);
	}
	file.close();
	console.out(0, 255, 0, "Success: File loaded!\n");
	return fileLoaded = true;
}

std::string ScheduleTracker::fileSelect()
{
	const char* command = "zenity --file-selection --title=\"Select a File\"";
	FILE *pipe = popen(command, "r");
	if (!pipe)
	{
		std::cerr << "Failed to run command\n";
		return "Zenity command error";
	}

	char buffer[256];
	std::string result = "";
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
	{
		result += buffer;
	}
	pclose(pipe);

	if (!result.empty())
	{
		result.erase(result.find_last_not_of(" \n\r\t") + 1);
		return result;
	}
	return "shedule.csv";
}

void ScheduleTracker::calculateAvgTime()
{
	long double minutes = 0;
	int week = 1;
	int days = 0;
	size_t itemNum = 0;
	std::pair<std::string, std::string> weekBound;
	for (ConsoleLib::TimeStamp& timeStamp : times)
	{
		minutes += ConsoleLib::TimeUtils::convertToMinutes(timeStamp);
		days++;
		itemNum++;
		// If 7 days collected or it's the last item
		if (days == 7 || itemNum == times.size() - 1)
		{
			weekBound = obtainWeekBounds(week - 1);

			std::cout << "Week " << week << " [" << weekBound.first << " - " << weekBound.second << "]" << ": " << (minutes / 60.0) / days;

			if (days < 7)
				std::cout << " (" << days << "/7)";
			std::cout << "\n";

			// Reset for next week
			days = 0;
			minutes = 0;
			week++;
		}
	}
}

void ScheduleTracker::printHeader()
{
	ConsoleLib::ConsoleUtils::header("\n    " + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION) + "\n   ", console);

	switch (lastEvent)
	{
		case ADD_TIMESTAMP:
			menu.enableLineBuffering();
			console.out("Enter: HOURS;MINUTES\n");
			std::getline(std::cin, line);
			writeFile(line, filename);
			menu.disableLineBuffering();
		break;
		case DISPLAY_DATA:
			if (!readFile())
				break;
			calculateAvgTime();
		break;
		default: break;
	}
	lastEvent = ButtonEvent::NONE;
}

std::pair<std::string, std::string> ScheduleTracker::obtainWeekBounds(const size_t weekIndex, const size_t daysPerWeek)
{
	size_t startIndex = weekIndex * daysPerWeek;

	if (startIndex >= dates.size())
	{
		throw std::out_of_range("Week index out of range");
	}

	size_t endIndex = std::min(startIndex + daysPerWeek - 1, dates.size() - 1);
	return { dates[startIndex], dates[endIndex] };
}

} /* namespace ConsoleArt */
