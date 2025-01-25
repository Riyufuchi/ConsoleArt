//==============================================================================
// File       : MessengerCLI.h
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : Apr 28, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CLI_MESSENGERCLI_H_
#define CONSOLEART_CLI_MESSENGERCLI_H_

#include <mutex>

#include "../tools/Messenger.h"
#include "IConsole.hpp"

namespace ConsoleArt
{
class MessengerCLI : public Messenger
{
	private:
		ConsoleLib::IConsole* console;
		std::mutex mutexPrintMessage;
	public:
		MessengerCLI(ConsoleLib::IConsole* console);
		virtual ~MessengerCLI();
		void messageUser(MessageType messageSeverity, std::string message) override;
		// Setters
		void setConsole(ConsoleLib::IConsole* console);
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_CLI_MESSENGERCLI_H_ */
