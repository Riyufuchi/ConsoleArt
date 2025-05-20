//==============================================================================
// File       : Messenger.h
// Author     : Riyufuchi
// Created on : Apr 28, 2024
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLE_ART_CLI_CONSOLEM_ESSENGER_H_
#define _CONSOLE_ART_CLI_CONSOLEM_ESSENGER_H_

#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "DefaultConsole.h"
#include "../../images/Image.h"

namespace ConsoleArt
{

class AbstractNotifier
{
public:
	enum MessageType
	{
		EXCEPTION,
		ERROR,
		WARNING,
		SUCCESFUL_TASK,
		INFO,
		NOTIFICATION
	};
public:
	AbstractNotifier();
	virtual ~AbstractNotifier();
	void messageUser(const std::string& message);
	virtual void messageUser(MessageType messageSeverity, const std::string& message) = 0;
	virtual void displayImageInfo(const Images::Image& image) = 0;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_CLI_CONSOLEMESSENGER_H_ */
