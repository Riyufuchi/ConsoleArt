//==============================================================================
// File       : ControllerGuiZen.cpp
// Author     : Riyufuchi
// Created on : May 30, 2024
// Last edit  : May 30, 2024
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ControllerGuiZen.h"

namespace ConsoleArt
{
ControllerGuiZen::ControllerGuiZen(ConsoleLib::IConsole* console) : ControllerCLI(console)
{
}
ControllerGuiZen::~ControllerGuiZen()
{
}
std::string ControllerGuiZen::inputImageName()
{
	const char* command = "zenity --file-selection --title=\"Select a File\"";
	FILE* pipe = popen(command, "r");
	if (!pipe)
	{
		console->err("Failed to run zenity command\n");
		return "no-file";
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
	return "no-file";
}
} /* namespace ConsoleArt */
