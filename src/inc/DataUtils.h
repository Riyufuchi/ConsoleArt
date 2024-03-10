//==============================================================================
// File       : DataUtils.h
// Author     : riyufuchi
// Created on : Mar 8, 2024
// Last edit  : Mar 8, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleLib
//==============================================================================

#ifndef _DATA_UTILS_H_
#define _DATA_UTILS_H_

#include <string>

namespace DataUtility
{
class DataUtils
{
private:
public:
	DataUtils();
	~DataUtils();
	static bool isNumber(const std::string& s);
};
}
#endif
