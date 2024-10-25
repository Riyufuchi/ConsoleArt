//==============================================================================
// File       : OtherUtils.hpp
// Author     : riyufuchi
// Created on : Oct 25, 2024
// Last edit  : Oct 25, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef OTHER_IDISTRIBUTION_HPP_
#define OTHER_IDISTRIBUTION_HPP_

namespace Other
{
using u_bigInt = long double; // unsigned long long; - temporary solution as precision errors might occur
using bigDouble = long double;

class IDisribution
{
public:
	IDisribution() = default;
	virtual ~IDisribution() = default;
	/* Expected value */
	virtual bigDouble ex() = 0;
	virtual bigDouble varX() = 0;
};
}
#endif
