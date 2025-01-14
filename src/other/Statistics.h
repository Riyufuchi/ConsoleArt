//==============================================================================
// File       : Statistics.h
// Author     : riyufuchi
// Created on : Jan 12, 2025
// Last edit  : Jan 14, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_STATISTICS_H_
#define OTHER_STATISTICS_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric> // For std::accumulate

namespace Other
{

class Statistics
{
private:
	std::vector<double> data; // Store the dataset
	void sortData();
public:
	Statistics(); // Creates empty vector
	Statistics(const std::vector<double>& dataset);
	~Statistics();
	void addValue(double value);
	void addValues(const std::vector<double>& values); // Add multiple values
	double mean(); // Calculate the mean (average) or expected value E(X) in this context
	double median(); // Calculate the median (middle value)
	double variance(bool sampleVarinace); // Calculate the variance (not standardized)
	double varianceWelford(bool sampleVarinace); // Calculate the variance using Welford's method (not standardized)
	double stadardizeVarX(double variance2); // Just square root, for better code readability
	std::vector<double> mode(); // Calculate the mode (most frequent value)
	std::vector<std::pair<std::string, double>> calculateStatistics(bool sampleData);
};

} /* namespace ConsoleArt */

#endif /* OTHER_STATISTICS_H_ */
