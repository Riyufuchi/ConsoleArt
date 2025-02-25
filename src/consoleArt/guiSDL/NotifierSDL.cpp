//==============================================================================
// File       : NotifierSDL.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "NotifierSDL.h"

namespace ConsoleArt
{

NotifierSDL::NotifierSDL()
{

}

NotifierSDL::~NotifierSDL()
{
}

void NotifierSDL::displayImageInfo(const Images::Image &image)
{
}

void NotifierSDL::messageUser(MessageType messageSeverity, std::string message)
{
	std::thread t([&]()
	{
		tinyfd_messageBox("Information", message.c_str(),  "ok", "info", 1);
	}); // Prevents blocking dialog from blocking main window thread and freezing whole app
	t.join(); // One dialog at time
}

} /* namespace ConsoleArt */
