//==============================================================================
// File       : NotifierSDL.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_NOTIFIERSDL_H_
#define CONSOLEART_GUISDL_NOTIFIERSDL_H_

#include <thread>

#include "../abstract/AbstractNotifier.h"

#include "../../include/tinyfiledialogs.h"


namespace ConsoleArt
{
class NotifierSDL : public AbstractNotifier
{
public:
	NotifierSDL();
	~NotifierSDL();
	virtual void displayImageInfo(const Images::Image &image) override;
	virtual void messageUser(MessageType messageSeverity, std::string message) override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUISDL_NOTIFIERSDL_H_ */
