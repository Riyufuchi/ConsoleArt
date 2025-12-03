//==============================================================================
// File       : SheduleTracker.h
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : May 09, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: consoleart
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
	std::string filename;
	std::vector<consolelib::TimeStamp> times;
	std::vector<std::string> menuTexts, dates;
	consolelib::IConsole& console;
	bool fileLoaded;
	ButtonEvent lastEvent;
	std::string line;
	consolelib::ConsoleMenu menu;
	bool readFile();
	bool addNewDataEntry();
	void calculateAvgTime();
	void convertToLong(long& destination, std::string& number);
	std::string selectFile();
	void printHeader();
	std::pair<std::string, std::string> obtainWeekBounds(const size_t weekIndex, const size_t daysPerWeek = 7);
	bool inputNewTimeStamp();
	bool isFormatValid();
public:
	ScheduleTracker(consolelib::IConsole& console);
	~ScheduleTracker();
	void run();
};
} /* namespace consoleart */
#endif /* OTHER_SHEDULETRACKER_H_ */
