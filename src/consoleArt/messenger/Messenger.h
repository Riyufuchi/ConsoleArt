//==============================================================================
// File       : Messenger.h
// Author     : Riyufuchi
// Created on : Apr 28, 2024
// Last edit  : Apr 28, 2024
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLE_ART_CLI_CONSOLEM_ESSENGER_H_
#define _CONSOLE_ART_CLI_CONSOLEM_ESSENGER_H_

#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "DefaultConsole.h"

namespace ConsoleArt
{

class Messenger
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
	protected:
	ConsoleLib::Color colors[6] = {
		ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::COLLECTORS), // Exception
		ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::STRANGE), // Error
		ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::UNIQUE), // Warning
		ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::COMMUNITY), // TAKS DONE
		ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::CONSOLE_ART_UNIX_DEFAULT), // Info
		ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::HAUNTED) // Notification
	};
	public:
	Messenger();
	virtual ~Messenger();
	virtual void messageUser(MessageType messageSeverity, std::string message) = 0;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_CLI_CONSOLEMESSENGER_H_ */
