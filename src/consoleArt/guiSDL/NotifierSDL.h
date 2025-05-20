//==============================================================================
// File       : NotifierSDL.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_NOTIFIERSDL_H_
#define CONSOLEART_GUISDL_NOTIFIERSDL_H_

#include <thread>

#include "../tinyFileDialogs/NotifierTFD.h"

namespace ConsoleArt
{
class NotifierSDL : public NotifierTFD
{
public:
	NotifierSDL();
	~NotifierSDL();
	virtual void displayImageInfo(const Images::Image& image) override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUISDL_NOTIFIERSDL_H_ */
