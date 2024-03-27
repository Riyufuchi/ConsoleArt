//==============================================================================
// File       : SheduleTracker.h
// Author     : riyufuchi
// Created on : Mar 26, 2024
// Last edit  : Mar 26, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
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

namespace Other
{
class SheduleTracker
{
private:
	static constexpr const char* filename = "stat.csv";
	std::vector<DataUtility::TimeStamp> times;
	ConsoleLib::IConsole* console;
	bool readFile();
public:
	SheduleTracker(ConsoleLib::IConsole* console);
	virtual ~SheduleTracker();
	void calculateAvgTime();
};
} /* namespace ConsoleArt */
#endif /* OTHER_SHEDULETRACKER_H_ */
