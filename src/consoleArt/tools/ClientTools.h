//==============================================================================
// File       : ClientTools.h
// Author     : Riyufuchi
// Created on : Mar 16, 2024
// Last edit  : Mar 19, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLEART_TOOLS_CLIENT_TOOLS_H_
#define _CONSOLEART_TOOLS_CLIENT_TOOLS_H_

#include <string>
#include <thread>

#include "../../inc/Client.h"
#include "../../inc/IConsole.hpp"

namespace ConsoleArt
{
class ClientTools
{
private:
	SufuServer::Client client;
	std::string sharedString;
	ConsoleUtility::IConsole& console;
	void handleResponse();
	void handleChat();
public:
	ClientTools(ConsoleUtility::IConsole& console);
	ClientTools(ConsoleUtility::IConsole& console, const char* ipAdress);
	virtual ~ClientTools();
	bool runClient();
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_TOOLS_CLIENTTOOLS_H_ */