//==============================================================================
// File       : NotifierCLI.cpp
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : Feb 18, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "NotifierCLI.h"

namespace ConsoleArt
{

NotifierCLI::NotifierCLI(ConsoleLib::IConsole* console) : console(console)
{
}

NotifierCLI::~NotifierCLI()
{
}

void NotifierCLI::setConsole(ConsoleLib::IConsole* console)
{
	this->console = console;
}

void NotifierCLI::messageUser(MessageType messageSeverity, std::string message)
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
void NotifierCLI::displayImageInfo(const Images::Image& image)
{
	if (!image)
		return;
	console->enableCustomFG();
	const Images::ImageInfo& info = image.getImageInfo();
	std::cout << "Name: " << info.name << "\n";
	std::cout << "Width: " << info.width << " px\n";
	std::cout << "Height: " << info.height << " px\n";
	std::cout << "Type: " << info.bits << " bit\n";
	std::cout << "Inverted: " << (image.isInverted() ? "Yes" : "No") << "\n";
	console->disableCustomFG();
}

} /* namespace ConsoleArt */
