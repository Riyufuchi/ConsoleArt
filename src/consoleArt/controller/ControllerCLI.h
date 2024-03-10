//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Mar 8, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLERCLI_H_
#define CONSOLEART_CONTROLLERCLI_H_

#include "Controller.h"
#include "../cli/AsciiPrinter.h"
#include "../../imageUtils/ImageToolsCLI.h"
#include "../../inc/ColorUtils.h"
#include "../../inc/ConsoleUtils.h"
#include "../../inc/UnixConsole.h"
#include "../../inc/DefaultConsole.h"
#include "../../inc/DataUtils.h"
#include "../cli/MenusCLI.h"

namespace ConsoleArt
{
class ControllerCLI : public Controller
{
private:
	ConsoleUtility::Color colors[6] = {
			ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::COLLECTORS), // Exception
			ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::STRANGE), // Error
			ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::UNIQUE), // Warning
			ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::COMMUNITY), // TAKS DONE
			ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::CONSOLE_ART_UNIX_DEFAULT), // Info
			ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::HAUNTED) // Notification
	};
	ConsoleUtility::IConsole* console;
	ConsoleUtility::DefaultConsole defaultConsole;
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
	ControllerCLI(ConsoleUtility::IConsole* console);
	ControllerCLI(std::string path, ConsoleUtility::IConsole* console);
	void configure(int argc, char** argv) override;
	void run() override;
	ConsoleUtility::IConsole* getConsole()
	{
		return console;
	}
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */
