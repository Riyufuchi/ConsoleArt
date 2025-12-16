//==============================================================================
// File       : DataUtils.h
// Author     : riyufuchi
// Created on : Mar 08, 2024
// Last edit  : Dec 16, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: consolelib
//==============================================================================

#ifndef _DATA_UTILS_H_
#define _DATA_UTILS_H_

#include <string>
#include <stdexcept>

namespace consolelib
{
class DataUtils
{
private:
public:
	DataUtils();
	~DataUtils();
	static bool isNumber(const std::string& s);
	static bool isDouble(const std::string& s);
	static std::string boolToString(bool value);
	static std::u32string string_to_u32string(const std::string& s);
	static std::string u32char_to_string(char32_t cp);

};
}
#endif
