//==============================================================================
// File       : NotifierSDL.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : May 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_NOTIFIERSDL_H_
#define CONSOLEART_GUISDL_NOTIFIERSDL_H_

#include <thread>

#include "../../../console_art/gui/tinyFileDialogs/NotifierTFD.h"

namespace consoleart
{
class NotifierSDL : public NotifierTFD
{
public:
	NotifierSDL();
	~NotifierSDL();
	virtual void displayImageInfo(const consoleartlib::Image& image) override;
	virtual void messageUser(AbstractNotifier::MessageType messageSeverity, const std::string& message) override;
};

} /* namespace consoleart */

#endif /* CONSOLEART_GUISDL_NOTIFIERSDL_H_ */
