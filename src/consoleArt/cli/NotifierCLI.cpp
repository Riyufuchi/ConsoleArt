//==============================================================================
// File       : NotifierCLI.cpp
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : Nov 07, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "NotifierCLI.h"

namespace ConsoleArt
{

NotifierCLI::NotifierCLI(consolelib::IConsole* console) : console(console)
{
}

NotifierCLI::~NotifierCLI()
{
}

void NotifierCLI::setConsole(consolelib::IConsole* console)
{
	this->console = console;
}

void NotifierCLI::messageUser(MessageType messageSeverity, const std::string& message)
{
	std::lock_guard<std::mutex> lock(mutexPrintMessage);
	switch(messageSeverity)
	{
		// Errors
		case EXCEPTION: console->err(exception, message); break;
		case ERROR: console->err(error, message); break;
		// Messages
		case WARNING: console->out(warning, message); break;
		case SUCCESFUL_TASK: console->out(taskDone, message); break;
		case NOTIFICATION:
			console->out(notification, message);
			std::cout << "\a";
		break;
		case INFO: console->out(info, message); break;
	}
}
void NotifierCLI::displayImageInfo(const Images::Image& image)
{
	if (!image)
		return;
	console->enableCustomFG();
	std::cout << image << "\n";
	console->disableCustomFG();
}

} /* namespace ConsoleArt */
