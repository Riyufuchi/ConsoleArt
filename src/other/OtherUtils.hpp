//==============================================================================
// File       : OtherUtils.hpp
// Author     : riyufuchi
// Created on : Oct 25, 2024
// Last edit  : Oct 25, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_OTHERUTILS_HPP_
#define OTHER_OTHERUTILS_HPP_

#include <iostream>

#include "BinomialDistribution.h"

namespace Other
{
class OtherhUtils
{
public:
	OtherhUtils();
	~OtherhUtils();
	static void distributeCards()
	{
		bigDouble result = 0;
		bigDouble united = 0;
		const int N = 50; // Number of packs in the box
		BinomialDistribution bi(10, (1.0L/230.L));
		const bigDouble CARD_IN_PACK_CHANCE = 1.0L - bi.distribute(0);
		printf("P(X > 1) = %Lf => %.2Lf %c\n", CARD_IN_PACK_CHANCE, (CARD_IN_PACK_CHANCE*100), '%');
		bi.setN(N);
		bi.setP(CARD_IN_PACK_CHANCE);
		for (int i = 1; i <= N; i++)
		{
			result = bi.distribute(i);
			united += result;
			std::cout << "P(" << i << ") = " << (result*100) << " %\n";
		}
		printf("P(X > 1) = P(1) ⋃ ... ⋃  P(%d) = %Lf => %.2Lf %c\n", N, united, united*100, '%');
		result = bi.distribute(0);
		printf("P(X = 0) = %Lf => %.2Lf %c\n", result, result*100, '%');
		result = 1.0L - result;
		printf("P(X > 1) = 1 - P(0) = %Lf => %.2Lf %c\n", result, result*100, '%');
		printf("EX = %Lf\n", bi.ex());
		printf("varX = %Lf\n", bi.varX());
	}
};
}
#endif /* OTHER_OTHERUTILS_HPP_ */
