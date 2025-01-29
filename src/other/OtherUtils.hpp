//==============================================================================
// File       : OtherUtils.hpp
// Author     : riyufuchi
// Created on : Oct 25, 2024
// Last edit  : Jan 29, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_OTHERUTILS_HPP_
#define OTHER_OTHERUTILS_HPP_

#include <iostream>
#include <cmath>
#include <vector>

namespace Other
{
class OtherhUtils
{
public:
	OtherhUtils();
	~OtherhUtils();
	template <typename K, typename T>
	static void printResults(const std::vector<std::pair<K, T>>& data)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(42);
		std::cout << "\n";
		for (const std::pair<K, T>& dataPair : data)
			std::cout << dataPair.first << dataPair.second << "\n";
		std::cout << "\n";
	}
};
}
#endif /* OTHER_OTHERUTILS_HPP_ */
