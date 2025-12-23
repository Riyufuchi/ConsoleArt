//==============================================================================
// File       : NotifierSDL.cpp
// Author     : riyufuchi
// Created on : May 16, 2025
// Last edit  : Nov 07, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../../console_art/gui/tinyFileDialogs/NotifierTFD.h"

namespace consoleart
{

NotifierTFD::NotifierTFD() : AbstractNotifier()
{

}

NotifierTFD::~NotifierTFD()
{
}

void NotifierTFD::displayImageInfo(const consoleartlib::Image& image)
{
	std::ostringstream message;
	message << image;
	tinyfd_messageBox("Image Info", message.str().c_str(), "ok", "info", 1);
}

void NotifierTFD::messageUser(MessageType messageSeverity, const std::string& message)
{
	switch(messageSeverity)
	{
		// Errors
		case EXCEPTION: tinyfd_messageBox("Exception", message.c_str(),  "ok", "error", 1); break;
		case PROBLEM: tinyfd_messageBox("Error", message.c_str(),  "ok", "error", 1); break;
		// Messages
		case WARNING: tinyfd_messageBox("Warning", message.c_str(),  "ok", "warning", 1); break;
		case SUCCESFUL_TASK: tinyfd_messageBox("Task successful", message.c_str(),  "ok", "info", 1); break;
		case NOTIFICATION: tinyfd_messageBox("Notification", message.c_str(), "ok", "info", 1); break;
		case INFO: tinyfd_messageBox("Information", message.c_str(), "ok", "info", 1); break;
	}
}

} /* namespace consoleart */
