//==============================================================================
// File       : NotifierZenity.cpp
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "NotifierZenity.h"

namespace consoleart {

NotifierZenity::NotifierZenity(consolelib::IConsole* console) : NotifierCLI(console)
{

}

NotifierZenity::~NotifierZenity()
{
}

void NotifierZenity::showDialog(const std::string& type, const std::string& text, MessageType messageSeverity)
{
	if (std::system(std::format("zenity {} --text=\"{}\" --width=200 --height=100", type, text).c_str()))
		NotifierCLI::messageUser(messageSeverity, text);
}

void NotifierZenity::displayImageInfo(const consoleartlib::Image& image)
{
	std::ostringstream cmd;
	cmd << "zenity --list --title='Image info' --width=600 --height=400 --column='Image name' --column='Width' --column='Height' --column='Bits' --column='Inverted' --column='Planar' ";
	const consoleartlib::ImageInfo& info = image.getImageInfo();
	cmd << "'" << info.name << "' " << info.width << " " << info.height << " " << info.bits << " " << (image.isInverted() ? "Yes" : "No") << " "
	<< consolelib::DataUtils::boolToString(info.planar);
	if (std::system(cmd.str().c_str()))
		NotifierCLI::displayImageInfo(image);

}

void NotifierZenity::messageUser(MessageType messageSeverity, const std::string& message)
{
	switch(messageSeverity)
	{
		// Errors
		case EXCEPTION:
		case PROBLEM: showDialog("--error", message, messageSeverity); break;
		// Messages
		case WARNING: showDialog("--warning", message, messageSeverity); break;
		case SUCCESFUL_TASK: showDialog("--info", message, messageSeverity); break;
		case NOTIFICATION: showDialog("--notification", message, messageSeverity); break;
		case INFO: showDialog("--info", message, messageSeverity); break;
	}
}
} /* namespace consoleart */
