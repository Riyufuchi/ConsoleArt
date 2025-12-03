//==============================================================================
// File       : NotifierCLI.h
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_CLI_NOTIFIERCLI_H_
#define CONSOLEART_CLI_NOTIFIERCLI_H_

#include <mutex>

#include "IConsole.hpp"
#include "../abstract/AbstractNotifier.h"

namespace consoleart
{
class NotifierCLI : public AbstractNotifier
{
	private:
		consolelib::Color warning = consolelib::ColorUtils::getColor(consolelib::ColorPallete::UNIQUE);
		consolelib::Color error = consolelib::ColorUtils::getColor(consolelib::ColorPallete::STRANGE);
		consolelib::Color exception = consolelib::ColorUtils::getColor(consolelib::ColorPallete::COLLECTORS);
		consolelib::Color taskDone = consolelib::ColorUtils::getColor(consolelib::ColorPallete::COMMUNITY);
		consolelib::Color info = consolelib::ColorUtils::getColor(consolelib::ColorPallete::CONSOLE_ART_UNIX_DEFAULT);
		consolelib::Color notification = consolelib::ColorUtils::getColor(consolelib::ColorPallete::HAUNTED);
		consolelib::IConsole* console;
	protected:
		std::mutex mutexPrintMessage;
	public:
		NotifierCLI(consolelib::IConsole* console);
		virtual ~NotifierCLI();
		void messageUser(MessageType messageSeverity, const std::string& message) override;
		void displayImageInfo(const consoleartlib::Image& image) override;
		// Setters
		void setConsole(consolelib::IConsole* console);
};
} /* namespace consoleart */
#endif /* CONSOLEART_CLI_NOTIFIERCLI_H_ */
