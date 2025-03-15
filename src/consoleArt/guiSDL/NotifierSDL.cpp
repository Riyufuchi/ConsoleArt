//==============================================================================
// File       : NotifierSDL.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Mar 8, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "NotifierSDL.h"

namespace ConsoleArt
{

NotifierSDL::NotifierSDL() : AbstractNotifier()
{

}

NotifierSDL::~NotifierSDL()
{
}

void NotifierSDL::displayImageInfo(const Images::Image& image)
{
	std::thread([&image]()
	{
		const Images::ImageInfo &info = image.getImageInfo();
		std::ostringstream message;
		message << "Image Name: " << info.name << "\n"
				<< "Width: " << info.width << " px\n"
				<< "Height: " << info.height << " px\n"
				<< "Bits: " << info.bits << "\n"
				<< "Inverted: " << (image.isInverted() ? "Yes" : "No") << "\n"
				<< "Planar: " << ConsoleLib::DataUtils::boolToString(info.planar);
		tinyfd_messageBox("Image Info", message.str().c_str(), "ok", "info", 1);
	}).detach(); // Shows the dialog (blocking, but running in another thread)
}

void NotifierSDL::messageUser(MessageType messageSeverity, std::string message)
{
	switch(messageSeverity)
	{
		// Errors
		case EXCEPTION: tinyfd_messageBox("Exception", message.c_str(),  "ok", "error", 1); break;
		case ERROR: tinyfd_messageBox("Error", message.c_str(),  "ok", "error", 1); break;
		// Messages
		case WARNING: tinyfd_messageBox("Warning", message.c_str(),  "ok", "warning", 1); break;
		case SUCCESFUL_TASK: tinyfd_messageBox("Task successful", message.c_str(),  "ok", "info", 1); break;
		case NOTIFICATION: tinyfd_messageBox("Notification", message.c_str(), "ok", "info", 1); break;
		case INFO: tinyfd_messageBox("Information", message.c_str(), "ok", "info", 1); break;
	}
}

} /* namespace ConsoleArt */
