//==============================================================================
// File       : ControllerTFD.cpp
// Author     : riyufuchi
// Created on : May 15, 2025
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ControllerTFD.h"

namespace ConsoleArt
{

ControllerTFD::ControllerTFD(ConsoleLib::IConsole* console) : ControllerCLI(console)
{
	setenv("TINYFD_FORCE_XDG", "1", 1);
	setMenu(new MenuTFD(this->console, [&]{ printHeader(); }));
	setNotifier(new NotifierTFD());
}

void ControllerTFD::printHeader()
{
	ConsoleLib::ConsoleUtils::header("\n    " + std::string(ConsoleArt::GeneralTools::CONSOLE_ART_VERSION) + "\n   ", *console);
	console->out("\nSelected image: ");
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

} /* namespace ConsoleLib */
