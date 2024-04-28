//==============================================================================
// File       : SheduleTracker.h
// Author     : Riyufuchi
// Created on : Mar 26, 2024
// Last edit  : Apr 28, 2024
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

namespace Other
{
class ScheduleTracker
{
private:
	static constexpr const char* filename = "stat.csv";
	std::vector<DataUtility::TimeStamp> times;
	ConsoleLib::IConsole* console;
	bool fileLoaded;
	bool readFile();
	bool writeFile(const std::string& line, const std::string& filename);
	void calculateAvgTime();
	void convertToLong(long& destination, std::string& number);
public:
	ScheduleTracker(ConsoleLib::IConsole* console);
	~ScheduleTracker();
	void menu();
};
} /* namespace ConsoleArt */
#endif /* OTHER_SHEDULETRACKER_H_ */
