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
#include "AsciiPrinter.h"
#include "../imageUtils/ImageToolsCLI.h"
#include "../inc/Colors.h"
#include "../inc/ConsoleUtility.h"
#include "../inc/UnixConsole.h"
#include "../consoleArt/MenuUtils.hpp"

namespace ConsoleArt
{
class ControllerCLI : public Controller
{
private:
	ConsoleUtils::Color colors[5] = {
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorUtils::ColorPallete::COLLECTORS),
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorUtils::ColorPallete::UNIQUE),
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorUtils::ColorPallete::STRANGE),
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorUtils::ColorPallete::COMMUNITY),
			ConsoleUtils::ColorUtils::getColor(ConsoleUtils::ColorUtils::ColorPallete::CONSOLE_ART_UNIX_DEFAULT)
	};
	ConsoleUtils::IConsole& console;
	void convertImage(Images::Image* image) override;
	void confConsoleColor() override;
	std::string inputImageName() override;
	Images::Image* selectImage() override;
	void messageUser(MessageSeverity messageSeverity, std::string message) override
	{
		switch(messageSeverity)
		{
			// Errors
			case EXCEPTION:
			case ERROR: console.err(colors[messageSeverity], message); break;
			// Messages
			case WARNING:
			case SUCCESFUL_TASK:
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
