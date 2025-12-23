//==============================================================================
// File       : ControllerTFD.cpp
// Author     : riyufuchi
// Created on : May 15, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../console_art/controller/ControllerTFD.h"

namespace consoleart
{

ControllerTFD::ControllerTFD(consolelib::IConsole* console) : ControllerCLI(console)
{
	setMenu(new MenuTFD(this->console, [&]{ printHeader(); }));
	setNotifier(new NotifierTFD());
}

void ControllerTFD::printHeader()
{
	consolelib::console_tools::header("\n    " + std::string(consoleart::general_tools::CONSOLE_ART_VERSION) + "\n   ", *console);
	console->out("\nSelected image: ");
	static consoleartlib::Image* selectedImage = getSelectedImage();
	if (selectedImage != nullptr)
		console->out(selectedImage->getFilename());
	else
		console->out("None");
	std::cout << "\n\n";
}

std::string ControllerTFD::inputImageName()
{
	std::vector<std::string> formatStrings;
	std::vector<char*> formatCStrs;
	for (const auto& p : supportedImageFormats)
	{
		formatStrings.push_back("*" + p.first);
		formatCStrs.push_back(strdup(formatStrings.back().c_str())); // Duplicate for C compatibility
	}
	const char* result = tinyfd_openFileDialog("Select an Image", workspacePath.c_str(), formatCStrs.size(), formatCStrs.data(), "Image Files", 0);
	if (result)
		return std::string(result);
	return "";
}

void ControllerTFD::showAboutApplicationInfo()
{
	ControllerCLI::showAboutApplicationInfo();
	console->out("Press enter to continue...");
	consolelib::console_tools::waitForEnter();
}

} /* namespace consolelib */
