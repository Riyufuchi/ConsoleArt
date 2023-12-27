//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Dec 18, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLERCLI_H_
#define CONSOLEART_CONTROLLERCLI_H_

#include "Controller.h"
#include "cli/AsciiPrinter.h"
#include "../imageUtils/ImageToolsCLI.h"
#include "../inc/ColorUtils.h"
#include "../inc/ConsoleUtility.h"
#include "../inc/UnixConsole.h"
#include "cli/MenusCLI.hpp"

namespace ConsoleArt
{
class ControllerCLI : public Controller
{
private:
	ConsoleUtils::Color colors[6] = {
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::COLLECTORS), // Exception
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::UNIQUE), // Error
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::STRANGE), // Warning
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::COMMUNITY), // TAKS DONE
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::CONSOLE_ART_UNIX_DEFAULT), // Info
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorPallete::HAUNTED) // Notification
	};
	ConsoleUtils::IConsole& console;
	MenusCLI menuCLI;
	void convertImage(Images::Image* image) override;
	void confConsoleColor() override;
	std::string inputImageName() override;
	Images::Image* selectImage() override;
	void messageUser(MessageType messageSeverity, std::string message) override
	{
		switch(messageSeverity)
		{
			// Errors
			case EXCEPTION:
			case ERROR: console.err(colors[messageSeverity], message); break;
			// Messages
			case WARNING:
			case SUCCESFUL_TASK:
			case NOTIFICATION:
			case INFO: console.out(colors[messageSeverity], message); break;
		}
	}
public:
	ControllerCLI(ConsoleUtils::IConsole& console);
	ControllerCLI(std::string path, ConsoleUtils::IConsole& console);
	void run() override;
	ConsoleUtils::IConsole& getConslole()
	{
		return console;
	}
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */
