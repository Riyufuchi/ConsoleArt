//==============================================================================
// File       : OtherUtils.hpp
// Author     : riyufuchi
// Created on : Oct 25, 2024
// Last edit  : Nov 08, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_DISTRIBUTION_H_
#define OTHER_DISTRIBUTION_H_

#include <math.h>

namespace Math
{
using u_bigInt = long double; // unsigned long long; - temporary solution as precision errors might occur
using bigDouble = long double;

class Disribution
{
protected:
	u_bigInt resultHolder;
public:
	Disribution();
	virtual ~Disribution() = default;
	u_bigInt factorial(int number);
	bigDouble power(bigDouble number, int power);
	virtual bigDouble distribute(int k) = 0;
	virtual bigDouble ex() = 0; // Expected value
	virtual bigDouble varX() = 0;
};
}
#endif
