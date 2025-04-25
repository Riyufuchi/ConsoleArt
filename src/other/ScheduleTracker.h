//==============================================================================
// File       : SheduleTracker.h
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : Apr 24, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _OTHER_SHEDULE_TRACKER_H_
#define _OTHER_SHEDULE_TRACKER_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "TimeUtils.h"
#include "IConsole.hpp"
#include "DefaultConsole.h"
#include "ConsoleUtils.h"
#include "ConsoleMenu.h"
#include "../consoleArt/tools/GeneralTools.hpp"

namespace Other
{
class ScheduleTracker
{
private:
	enum ButtonEvent
	{
		NONE,
		ADD_TIMESTAMP,
		DISPLAY_DATA,
		EXIT
	};
	static constexpr const char* filename = "stat.csv";
	std::vector<ConsoleLib::TimeStamp> times;
	ConsoleLib::IConsole& console;
	bool fileLoaded;
	ButtonEvent lastEvent;
	std::string line;
	std::vector<std::string> menuTexts;
	ConsoleLib::ConsoleMenu menu;
	bool readFile();
	bool writeFile(const std::string& line, const std::string& filename);
	void calculateAvgTime();
	void convertToLong(long& destination, std::string& number);
	std::string fileSelect();
	void printHeader();
public:
	ScheduleTracker(ConsoleLib::IConsole& console);
	~ScheduleTracker();
	void run();
};
} /* namespace ConsoleArt */
#endif /* OTHER_SHEDULETRACKER_H_ */
