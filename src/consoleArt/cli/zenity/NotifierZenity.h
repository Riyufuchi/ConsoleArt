//==============================================================================
// File       : NotifierZenity.h
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CLIZENITY_NOTIFIERZENITY_H_
#define CONSOLEART_CLIZENITY_NOTIFIERZENITY_H_

#include <format>

// consolelib
#include <DataUtils.h>

#include "../NotifierCLI.h"

namespace ConsoleArt
{
class NotifierZenity : public NotifierCLI
{
private:
	std::string dialogTypeHolder;
	void showDialog(const std::string& type, const std::string& text, MessageType messageSeverity);
public:
	NotifierZenity(consolelib::IConsole* console);
	~NotifierZenity();
	virtual void displayImageInfo(const Images::Image& image) override;
	virtual void messageUser(MessageType messageSeverity, const std::string& message) override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_CLIZENITY_NOTIFIERZENITY_H_ */
