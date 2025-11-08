//==============================================================================
// File       : PoissonsDistribution.cpp
// Author     : riyufuchi
// Created on : Nov 1, 2024
// Last edit  : Nov 08, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "PoissonsDistribution.h"

namespace Math
{
PoissonsDistribution::PoissonsDistribution(int lambda) : λ(lambda)
{
}
PoissonsDistribution::~PoissonsDistribution()
{
}
bigDouble PoissonsDistribution::distribute(int k)
{
	return (pow(λ, k)*pow(M_E, -1*λ))/factorial(k);
}
bigDouble PoissonsDistribution::ex()
{
	return λ;
}
bigDouble PoissonsDistribution::varX()
{
	return λ;
}
} /* namespace Other */
