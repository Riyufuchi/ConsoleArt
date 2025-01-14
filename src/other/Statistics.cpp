//==============================================================================
// File       : Statistics.cpp
// Author     : riyufuchi
// Created on : Jan 12, 2025
// Last edit  : Jan 14, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Statistics.h"

namespace Other {

Statistics::Statistics()
{
	this->data = std::vector<double>();
}
Statistics::Statistics(const std::vector<double>& dataset) : data(dataset)
{
}

Statistics::~Statistics()
{
}

void Statistics::sortData()
{
	std::sort(data.begin(), data.end());
}

void Statistics::addValue(double value)
{
	data.push_back(value);
}

void Statistics::addValues(const std::vector<double>& values)
{
	data.insert(data.end(), values.begin(), values.end());
}

double Statistics::mean()
{
	if (data.empty())
		return 0.0;
	return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double Statistics::median()
{
	if (data.empty())
		return 0.0;
	sortData();
	size_t size = data.size();
	if (size % 2 == 0)
		return (data[size / 2 - 1] + data[size / 2]) / 2.0; // Average of two middle values for even size
	else
		return data[size / 2]; // Middle value for odd size
}

double Statistics::variance(bool sampleVarinace)
{
	if (data.size() < 2)
		return 0.0;
	double meanValue = mean(); // EX
	double sum = 0.0;
	for (double value : data)
		sum += std::pow(value - meanValue, 2);
	if (sampleVarinace)
		return sum / (data.size() - 1);
	return sum / data.size();
}

double Statistics::varianceWelford(bool sampleVarinace)
{
	if (data.size() < 2)
		return 0.0;

	double meanValue = 0.0, M2 = 0.0;
	int count = 0;
	double delta = 0.0;

	for (double value : data)
	{
		count++;
		delta = value - meanValue;
		meanValue += delta / count;
		M2 += delta * (value - meanValue);
	}

	if (sampleVarinace)
		return M2 / (data.size() - 1); // For sample variance
	return M2 / data.size(); // For population variance
}

double Statistics::stadardizeVarX(double variance2)
{
	return std::sqrt(variance2);
}

std::vector<double> Statistics::mode()
{
	if (data.empty())
		return {};
	std::map<double, int> frequency;
	for (double value : data)
		frequency[value]++;
	// Find the maximum frequency
	int maxFreq = 0;
	for (const auto& [key, count] : frequency)
		maxFreq = std::max(maxFreq, static_cast<int>(count));
	// Collect all values with the maximum frequency
	std::vector<double> modes;
	for (const auto& [key, count] : frequency)
		if (count == maxFreq)
			modes.push_back(static_cast<double>(key));
	return modes;
}

std::vector<std::pair<std::string, double>> Statistics::calculateStatistics(bool sampleData)
{
	std::vector<std::pair<std::string, double>> pairs;
	pairs.push_back(std::pair<std::string, double>("Mean (E[X]): ", mean()));
	pairs.push_back(std::pair<std::string, double>("Median: ", median()));
	pairs.push_back(std::pair<std::string, double>("Standard variance: ", stadardizeVarX(variance(sampleData))));
	pairs.push_back(std::pair<std::string, double>("Standard variance (Welford): ", stadardizeVarX(varianceWelford(sampleData))));
	auto modes = mode();
	if (!modes.empty())
		for (size_t i = 0; i < modes.size(); i++)
			pairs.push_back(std::pair<std::string, double>("Mode: ",  modes[i]));
	return pairs;
}

} /* namespace ConsoleArt */
