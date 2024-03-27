//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Mar 27, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLERCLI_H_
#define CONSOLEART_CONTROLLERCLI_H_

#include <chrono>

#include "Controller.h"
#include "../cli/AsciiPrinter.h"
#include "../cli/MenusCLI.h"
#include "../tools/ClientTools.h"
#include "../../imageUtils/ImageToolsCLI.h"
#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "DefaultConsole.h"
#include "DataUtils.h"

#include "../../other/SheduleTracker.h"

namespace ConsoleArt
{
class ControllerCLI : public Controller
{
private:
	ConsoleLib::Color colors[6] = {
			ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::COLLECTORS), // Exception
			ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::STRANGE), // Error
			ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::UNIQUE), // Warning
			ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::COMMUNITY), // TAKS DONE
			ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::CONSOLE_ART_UNIX_DEFAULT), // Info
			ConsoleLib::ColorUtils::getColor(ConsoleLib::ColorPallete::HAUNTED) // Notification
	};
	ConsoleLib::IConsole* console;
	ConsoleLib::DefaultConsole defaultConsole;
	MenusCLI menuCLI;
	void convertImage(Images::Image* image) override;
	std::string inputImageName() override;
	Images::Image* selectImage() override;
	void messageUser(MessageType messageSeverity, std::string message) override
	{
		switch(messageSeverity)
		{
			// Errors
			case EXCEPTION:
			case ERROR: console->err(colors[messageSeverity], message); break;
			// Messages
			case WARNING:
			case SUCCESFUL_TASK:
			case NOTIFICATION:
			case INFO: console->out(colors[messageSeverity], message); break;
		}
	}
public:
	ControllerCLI(ConsoleLib::IConsole* console);
	ControllerCLI(std::string path, ConsoleLib::IConsole* console);
	void configure(int argc, char** argv) override;
	void run() override;
	ConsoleLib::IConsole* getConsole()
	{
		return console;
	}
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */
