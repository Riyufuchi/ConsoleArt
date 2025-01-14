//==============================================================================
// File       : StatisticsGeneric.cpp
// Author     : riyufuchi
// Created on : Jan 14, 2025
// Last edit  : Jan 14, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "StatisticsGeneric.h"

namespace Other
{
template <typename T>
StatisticsGeneric<T>::StatisticsGeneric()
{
	this->data = std::vector<T>();
}
template <typename T>
StatisticsGeneric<T>::StatisticsGeneric(const std::vector<T>& dataset) : data(dataset)
{
}

template <typename T>
StatisticsGeneric<T>::~StatisticsGeneric()
{
}

template <typename T>
void StatisticsGeneric<T>::sortData()
{
	std::sort(data.begin(), data.end());
}

template <typename T>
void StatisticsGeneric<T>::addValue(T value)
{
	data.push_back(value);
}

template <typename T>
void StatisticsGeneric<T>::addValues(const std::vector<T>& values)
{
	data.insert(data.end(), values.begin(), values.end());
}

template <typename T>
T StatisticsGeneric<T>::mean()
{
	if (data.empty())
		return 0.0;
	return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

template <typename T>
T StatisticsGeneric<T>::median()
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

template <typename T>
T StatisticsGeneric<T>::variance(bool sampleVarinace)
{
	if (data.size() < 2)
		return 0.0;
	T meanValue = mean(); // EX
	T sum = 0.0;
	for (T value : data)
		sum += std::pow(value - meanValue, 2);
	if (sampleVarinace)
		return sum / (data.size() - 1);
	return sum / data.size();
}

template <typename T>
T StatisticsGeneric<T>::varianceWelford(bool sampleVarinace)
{
	if (data.size() < 2)
		return 0.0;

	T meanValue = 0.0, M2 = 0.0;
	int count = 0;
	T delta = 0.0;

	for (T value : data)
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

template <typename T>
T StatisticsGeneric<T>::stadardizeVarX(T variance2)
{
	return std::sqrt(variance2);
}

template <typename T>
std::vector<T> StatisticsGeneric<T>::mode()
{
	if (data.empty())
		return {};
	std::map<T, int> frequency;
	for (T value : data)
		frequency[value]++;
	// Find the maximum frequency
	int maxFreq = 0;
	for (const auto& [key, count] : frequency)
		maxFreq = std::max(maxFreq, static_cast<int>(count));
	// Collect all values with the maximum frequency
	std::vector<T> modes;
	for (const auto& [key, count] : frequency)
		if (count == maxFreq)
			modes.push_back(static_cast<T>(key));
	return modes;
}

template <typename T>
std::vector<std::pair<std::string, T>> StatisticsGeneric<T>::calculateStatistics(bool sampleData)
{
	std::vector<std::pair<std::string, T>> pairs;
	pairs.push_back(std::pair<std::string, T>("Mean (E[X]): ", mean()));
	pairs.push_back(std::pair<std::string, T>("Median: ", median()));
	pairs.push_back(std::pair<std::string, T>("Standard variance: ", stadardizeVarX(variance(sampleData))));
	pairs.push_back(std::pair<std::string, T>("Standard variance (Welford): ", stadardizeVarX(varianceWelford(sampleData))));
	auto modes = mode();
	if (!modes.empty())
		for (size_t i = 0; i < modes.size(); i++)
			pairs.push_back(std::pair<std::string, T>("Mode: ",  modes[i]));
	return pairs;
}

} /* namespace ConsoleArt */
