//==============================================================================
// File       : PoissonsDistribution.cpp
// Author     : riyufuchi
// Created on : Nov 1, 2024
// Last edit  : Nov 1, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "PoissonsDistribution.h"

namespace Other
{
PoissonsDistribution::PoissonsDistribution(int lambda) : λ(lambda)
{
}
PoissonsDistribution::~PoissonsDistribution()
{
}
Other::bigDouble PoissonsDistribution::distribute(int k)
{
	return (pow(λ, k)*pow(M_E, -1*λ))/factorial(k);
}
Other::bigDouble PoissonsDistribution::ex()
{
	return λ;
}
Other::bigDouble PoissonsDistribution::varX()
{
	return λ;
}
} /* namespace Other */
