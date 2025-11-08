//==============================================================================
// File       : Distribution.cpp
// Author     : riyufuchi
// Created on : Nov 1, 2024
// Last edit  : Nov 08, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Distribution.h"

namespace Math
{
Disribution::Disribution() : resultHolder(0)
{}
u_bigInt Disribution::factorial(int number)
{
	resultHolder = 1;
	for (int i = 2; i <= number; i++)
		resultHolder *= i;
	return resultHolder;
}
bigDouble Disribution::power(bigDouble number, int power)
{
	resultHolder = 1.0L;
	for (int i = 0; i < power; i++)
		resultHolder = number * resultHolder;
	return resultHolder;
}
}
