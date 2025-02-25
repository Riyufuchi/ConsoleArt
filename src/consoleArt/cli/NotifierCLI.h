//==============================================================================
// File       : NotifierCLI.h
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : Feb 13, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CLI_NOTIFIERCLI_H_
#define CONSOLEART_CLI_NOTIFIERCLI_H_

#include <mutex>

#include "IConsole.hpp"
#include "../tools/AbstractNotifier.h"

namespace ConsoleArt
{
class NotifierCLI : public AbstractNotifier
{
	private:
		ConsoleLib::IConsole* console;
	protected:
		std::mutex mutexPrintMessage;
	public:
		NotifierCLI(ConsoleLib::IConsole* console);
		virtual ~NotifierCLI();
		void messageUser(MessageType messageSeverity, std::string message) override;
		void displayImageInfo(const Images::Image& image) override;
		// Setters
		void setConsole(ConsoleLib::IConsole* console);
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_CLI_NOTIFIERCLI_H_ */
