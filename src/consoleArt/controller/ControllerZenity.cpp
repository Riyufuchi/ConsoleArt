//==============================================================================
// File       : ControllerZenity.cpp
// Author     : Riyufuchi
// Created on : May 30, 2024
// Last edit  : Jan 24, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ControllerZenity.h"

namespace ConsoleArt
{
ControllerZenity::ControllerZenity(ConsoleLib::IConsole* console) : ControllerCLI(console)
{
	messenger->messageUser(Messenger::MessageType::NOTIFICATION, "Started in CLI mode using zenity\n");
}
ControllerZenity::~ControllerZenity()
{
}
std::string ControllerZenity::inputImageName()
{
	std::string command = "zenity --file-selection --title=\"Select a File\" --filename=\"" + workspacePath + "\"";

	FILE* pipe = popen(command.c_str(), "r");
	if (!pipe)
	{
		console->err("Failed to run zenity command\n");
		return ControllerCLI::inputImageName();
	}
	char buffer[256];
	std::string result = "";
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
	{
		result += buffer;
	}
	pclose(pipe);
	if (!result.empty())
	{
		result.erase(result.find_last_not_of(" \n\r\t") + 1);
		return result;
	}
	return ControllerCLI::inputImageName();
}
} /* namespace ConsoleArt */
