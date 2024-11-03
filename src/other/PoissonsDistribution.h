//==============================================================================
// File       : PoissonsDistribution.h
// Author     : riyufuchi
// Created on : Nov 1, 2024
// Last edit  : Nov 1, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_POISSONSDISTRIBUTION_H_
#define OTHER_POISSONSDISTRIBUTION_H_

#include "Distribution.h"

namespace Other
{
class PoissonsDistribution: public Disribution
{
private:
	int λ;
public:
	PoissonsDistribution(int lambda);
	~PoissonsDistribution();
	virtual Other::bigDouble distribute(int k);
	virtual Other::bigDouble ex();
	virtual Other::bigDouble varX();
};

} /* namespace ConsoleArt */

#endif /* OTHER_POISSONSDISTRIBUTION_H_ */
