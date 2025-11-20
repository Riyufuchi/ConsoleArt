//==============================================================================
// File       : MathUtils.hpp
// Author     : riyufuchi
// Created on : Jan 29, 2025
// Last edit  : Nov 20, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_MATHUTILS_HPP_
#define OTHER_MATHUTILS_HPP_

#include <iostream>
#include <cmath>
#include <vector>

#include "distributions/BinomialDistribution.h"
#include "StatisticsGeneric.h"

namespace Math
{
class MathUtils
{
public:
	MathUtils() = default;
	~MathUtils() = default;
	// TODO: Make this function safe
	static std::vector<std::pair<int, long double>> binomialDistribution(const std::vector<std::string>& params) // vector[N, P, K...]
	{
		std::vector<std::pair<int, long double>> results;
		if (params.size() < 3)
		{
			distributeCards();
			results.emplace_back(std::pair<int, long double>(-1, -1));
			return results;
		}
		const int N = std::stoi(params.at(0));
		const long double P = parseStringToLD(params.at(1));
		if (P == -1)
		{
			std::cout << "Input " << params.at(1) << " is not a valid number!\n";
			return results;
		}
		std::vector<int> kArgs;
		for (size_t i = 2; i < params.size(); i++)
			kArgs.emplace_back(std::stoi(params.at(i)));
		Math::BinomialDistribution bi(N, P);
		for (size_t i = 0; i < kArgs.size(); i++)
			results.emplace_back(std::pair<int, long double>(kArgs.at(i), bi.distribute(kArgs.at(i))));
		return results;
	}
	static long double parseStringToLD(const std::string& s)
	{
		if (ConsoleLib::DataUtils::isDouble(s))
		{
			return std::stold(s);
		}
		else if (s.find('/') != std::string::npos)
		{
			std::vector<std::string> tokens;
			std::stringstream ss(s);
			std::string token;

			while (std::getline(ss, token, '/'))
			{
				if (!ConsoleLib::DataUtils::isDouble(token))
					return -1;
				tokens.push_back(token);
			}

			return std::stold(tokens.at(0)) / std::stold(tokens.at(1));
		}
		else
		{
			return -1;
		}
	}
	static void distributeCards()
	{
		const int N = 10; // Number of cards in the pack
		const int N_2= 50; // Number of packs in the box
		const Math::bigDouble P = (1.0L/230.0L);
		Math::bigDouble result = 0;
		Math::BinomialDistribution bi(N, P);
		const Math::bigDouble CARD_IN_PACK_CHANCE = 1.0L - bi.distribute(0);
		printf("X ~ Bi(%d, %Lf) = P(X > 1) = %Lf => %.2Lf %c\n", N, P, CARD_IN_PACK_CHANCE, (CARD_IN_PACK_CHANCE*100), '%');
		bi.setN(N_2);
		bi.setP(CARD_IN_PACK_CHANCE);
		result = bi.distribute(0);
		printf("P(X = 0) = %Lf => %.2Lf %c\n", result, result*100, '%');
		result = 1.0L - result;
		printf("P(X > 1) = 1 - P(0) = %Lf => %.2Lf %c\n", result, result*100, '%');
		printf("EX = %Lf\n", bi.ex());
		printf("varX = %Lf\n", bi.varX());
	}
	static void testMean()
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(16);
		std::vector<double> dataset = {30000, 30000, 25000, 30000, 40000, 50000, 100000, 50000};
		std::vector<double> dataset2 = {30000, 30000, 30000, 30000, 40000, 40000, 80000, 40000};
		std::vector<double> dataset3 = {0.25, 0.75, 0.50, 1, 0};
		std::vector<long double> dataset4 = {M_PI, M_E, M_PI*M_E, M_PI/M_E, M_E/M_PI};
		ConsoleLib::StatisticsGeneric<double> stats0(dataset);
		printResults<std::string, double>(stats0.calculateStatistics(false));
		ConsoleLib::StatisticsGeneric<double> stats2(dataset2);
		printResults<std::string, double>(stats2.calculateStatistics(false));
		ConsoleLib::StatisticsGeneric<double> stats3(dataset3);
		printResults<std::string, double>(stats3.calculateStatistics(false));
		ConsoleLib::StatisticsGeneric<long double> stats4(dataset4);
		printResults<std::string, long double>(stats4.calculateStatistics(false));
	}
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
