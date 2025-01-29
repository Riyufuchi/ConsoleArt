//==============================================================================
// File       : Statistics.h
// Author     : riyufuchi
// Created on : Jan 14, 2025
// Last edit  : Jan 14, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_STATISTICSGENERIC_H_
#define OTHER_STATISTICSGENERIC_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric> // For std::accumulate

namespace Math
{
template <typename T>
class StatisticsGeneric
{
private:
	std::vector<T> data; // Store the dataset
	void sortData();
public:
	StatisticsGeneric(); // Creates empty vector
	StatisticsGeneric(const std::vector<T>& dataset);
	~StatisticsGeneric();
	void addValue(T value);
	void addValues(const std::vector<T>& values); // Add multiple values
	T mean(); // Calculate the mean (average) or expected value E(X) in this context
	T median(); // Calculate the median (middle value)
	T variance(bool sampleVarinace); // Calculate the variance (not standardized)
	T varianceWelford(bool sampleVarinace); // Calculate the variance using Welford's method (not standardized)
	T stadardizeVarX(T variance2); // Just square root, for better code readability
	std::vector<T> mode(); // Calculate the mode (most frequent value)
	std::vector<std::pair<std::string, T>> calculateStatistics(bool sampleData);
};
}
#include "StatisticsGeneric.tpp"
#endif
