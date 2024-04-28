//==============================================================================
// File       : MessengerCLI.cpp
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : Apr 28, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "MessengerCLI.h"

namespace ConsoleArt
{

MessengerCLI::MessengerCLI(ConsoleLib::IConsole* console) : console(console)
{
}

MessengerCLI::~MessengerCLI()
{
}

void MessengerCLI::setConsole(ConsoleLib::IConsole* console)
{
	this->console = console;
}

void MessengerCLI::messageUser(MessageType messageSeverity, std::string message)
{
	std::lock_guard<std::mutex> lock(mutexPrintMessage);
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

} /* namespace ConsoleArt */
