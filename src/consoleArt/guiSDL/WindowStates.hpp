//==============================================================================
// File       : WindowStates.hpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Feb 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_WINDOWSTATES_HPP_
#define CONSOLEART_GUISDL_WINDOWSTATES_HPP_

#include "states/MainStateSDL.h"
#include "states/EditImageStateSDL.h"
#include "states/ImageStateSDL.h"

namespace ConsoleArt
{
enum WindowState
{
	MAIN,
	EDIT_IMAGE,
	SHOW_IMAGE
};
}
#endif /* CONSOLEART_GUISDL_WINDOWSTATES_HPP_ */
