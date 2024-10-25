//==============================================================================
// File       : BinomDistribution.cpp
// Author     : riyufuchi
// Created on : Oct 22, 2024
// Last edit  : Oct 25, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "BinomialDistribution.h"

namespace Other
{
BinomialDistribution::BinomialDistribution() : BinomialDistribution(1, 1)
{
}
BinomialDistribution::BinomialDistribution(int n, bigDouble p) : IDisribution(), resultHolder(0), n(n), p(p)
{
}

BinomialDistribution::~BinomialDistribution()
{
}
u_bigInt BinomialDistribution::factorial(int number)
{
	resultHolder = 1;
	for (int i = 2; i <= number; i++)
		resultHolder *= i;
	return resultHolder;
}
u_bigInt BinomialDistribution::partialFactorial(int number, int steps)
{
	resultHolder = 1;
	for (int i = number; i > steps; i--)
		resultHolder *= i;  // Multiply from 'number' down to 'steps + 1'
	return resultHolder;
}
u_bigInt BinomialDistribution::combinationNumber(int n, int k)
{
	if (k == 0 || k == n)
		return 1;
	if (k == 1)
		return n;
	return partialFactorial(n, n - k) / factorial(k);
}
bigDouble BinomialDistribution::power(bigDouble number, bigDouble power)
{
	resultHolder = number;
	for (int i = 1; i < power; i++)
		number = number * resultHolder;
	return number;
}
bigDouble BinomialDistribution::distribute(int k)
{
	return combinationNumber(n, k) * pow(p, k) * pow((1.0L - p), (n - k));
}
bigDouble BinomialDistribution::distribute(int k, bigDouble p, int n)
{
	return combinationNumber(n, k) * pow(p, k) * pow((1.0L - p), (n - k));
}
// Overrides
bigDouble BinomialDistribution::ex()
{
	return n*p;
}
bigDouble BinomialDistribution::varX()
{
	return n*p*(1 - p);
}
// Setters
void BinomialDistribution::setP(bigDouble p)
{
	this->p = p;
}
void BinomialDistribution::setN(int n)
{
	this->n = n;
}
// Getters
bigDouble BinomialDistribution::getP() const
{
	return p;
}
int BinomialDistribution::getN() const
{
	return n;
}
} /* namespace ConsoleArt */
