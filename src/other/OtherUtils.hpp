//==============================================================================
// File       : OtherUtils.hpp
// Author     : riyufuchi
// Created on : Oct 25, 2024
// Last edit  : Jan 14, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_OTHERUTILS_HPP_
#define OTHER_OTHERUTILS_HPP_

#include <iostream>
#include <cmath>

#include "BinomialDistribution.h"
#include "Statistics.h"
#include "StatisticsGeneric.h"

namespace Other
{
class OtherhUtils
{
public:
	OtherhUtils();
	~OtherhUtils();
	static void distributeCards()
	{
		const int N = 10; // Number of cards in the pack
		const int N_2= 50; // Number of packs in the box
		const bigDouble P = (1.0L/230.0L);
		bigDouble result = 0;
		BinomialDistribution bi(N, P);
		const bigDouble CARD_IN_PACK_CHANCE = 1.0L - bi.distribute(0);
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
	template <typename T>
	static void printResult(const std::vector<std::pair<std::string, T>>& data)
	{
		for (std::pair<std::string, T> dataPair : data)
			std::cout << dataPair.first << dataPair.second << "\n";
		std::cout << "\n";
	}
	static void testMean()
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(16);
		std::vector<double> dataset = {30000, 30000, 25000, 30000, 40000, 50000, 100000, 50000};
		std::vector<double> dataset2 = {30000, 30000, 30000, 30000, 40000, 40000, 80000, 40000};
		std::vector<double> dataset3 = {0.25, 0.75, 0.50, 1, 0};
		std::vector<long double> dataset4 = {M_PI, M_E, M_PI*M_E, M_PI/M_E, M_E/M_PI};
		Other::Statistics stats0(dataset);
		printResult<double>(stats0.calculateStatistics(false));
		Other::Statistics stats2(dataset2);
		printResult<double>(stats2.calculateStatistics(false));
		Other::Statistics stats3(dataset3);
		printResult<double>(stats3.calculateStatistics(false));
		Other::StatisticsGeneric<long double> stats4(dataset4);
		printResult<long double>(stats4.calculateStatistics(false));
	}
};
}
#endif /* OTHER_OTHERUTILS_HPP_ */
