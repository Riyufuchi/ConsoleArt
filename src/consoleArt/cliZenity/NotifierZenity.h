//==============================================================================
// File       : NotifierZenity.h
// Author     : riyufuchi
// Created on : Feb 24, 2025
// Last edit  : Feb 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CLIZENITY_NOTIFIERZENITY_H_
#define CONSOLEART_CLIZENITY_NOTIFIERZENITY_H_

#include <format>

#include "../cli/NotifierCLI.h"

namespace ConsoleArt
{
class NotifierZenity : public NotifierCLI
{
private:
	std::string dialogTypeHolder;
	void showDialog(std::string type, std::string& text, MessageType messageSeverity);
public:
	NotifierZenity(ConsoleLib::IConsole* console);
	~NotifierZenity();
	virtual void displayImageInfo(const Images::Image &image) override;
	virtual void messageUser(MessageType messageSeverity, std::string message) override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_CLIZENITY_NOTIFIERZENITY_H_ */
