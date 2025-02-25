//==============================================================================
// File       : ControllerZenity.cpp
// Author     : Riyufuchi
// Created on : May 30, 2024
// Last edit  : Feb 24, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ControllerZenity.h"

namespace ConsoleArt
{
ControllerZenity::ControllerZenity(ConsoleLib::IConsole* console) : ControllerCLI(console)
{
	if (menuCLI)
		delete menuCLI;
	this->menuCLI = new MenuZenity(console);
	if (messenger)
		delete messenger;
	this->messenger = new NotifierZenity(console);
	messenger->messageUser(AbstractNotifier::MessageType::NOTIFICATION, "Started in CLI mode using Zenity\n");
}
ControllerZenity::~ControllerZenity()
{
	std::cout << "ControllerZenity destroyed\n";
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

Images::Image* ControllerZenity::selectImage()
{
	if (images.empty())
	{
		std::cerr << "No images loaded!" << std::endl;
		return nullptr;
	}

	// Build the Zenity command
	std::ostringstream cmd;
	cmd << "zenity --list --title='Select an Image' --width=600 --height=400 --column='Image name' --column='Width' --column='Height' --column='Bits' --column='Inverted' ";

	for (const auto &img : images)
	{
		const Images::ImageInfo& info = img->getImageInfo();
		cmd << "'" << info.name << "' " << info.width << " " << info.height << " " << info.bits << " " << (img->isInverted() ? "Yes" : "No") << " ";
	}

	FILE *pipe = popen(cmd.str().c_str(), "r");
	if (!pipe)
	{
		std::cerr << "Failed to open Zenity list dialog!" << std::endl;
		return ControllerCLI::selectImage();
	}

	char buffer[256]; // Store selected filename
	if (fgets(buffer, sizeof(buffer), pipe) == nullptr)
	{
		pclose(pipe);
		return nullptr; // No selection (canceled)
	}

	pclose(pipe);

	// Remove trailing newline
	std::string selectedImage(buffer);
	selectedImage.erase(selectedImage.find_last_not_of("\n") + 1);

	for (std::unique_ptr<Images::Image>& img : images)
		if (img->getFilename() == selectedImage)
			return img.get();
	return nullptr;
}

void ControllerZenity::showAboutApplicationInfo()
{
	std::string command = "echo \"" + GeneralTools::aboutApplication() + "\" | zenity --text-info --title='About ConsoleArt' --width=600 --height=600";
	FILE* pipe = popen(command.c_str(), "r");
	if (!pipe)
	{
		ControllerCLI::showAboutApplicationInfo();
	}
	pclose(pipe);
}

} /* namespace ConsoleArt */
