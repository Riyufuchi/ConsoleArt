//==============================================================================
// File       : IMainState.h
// Author     : riyufuchi
// Created on : Feb 27, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_INTERFACES_IMAINSTATE_HPP_
#define CONSOLEART_INTERFACES_IMAINSTATE_HPP_

#include <string>

#include "../../images/Formats.hpp"

namespace ConsoleArt
{
class IMainState
{
public:
	IMainState() = default;
	virtual ~IMainState() = default;
	virtual std::string inputImageName() = 0;
	virtual Images::Image* selectImage() = 0;
	virtual void showAboutApplicationInfo() = 0;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_INTERFACES_IMAINSTATE_HPP_ */
