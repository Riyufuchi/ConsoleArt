//==============================================================================
// File       : ClientTools.h
// Author     : riyufuchi
// Created on : Mar 16, 2024
// Last edit  : Mar 16, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_TOOLS_CLIENTTOOLS_H_
#define CONSOLEART_TOOLS_CLIENTTOOLS_H_

#include <string>
#include <thread>

#include "../../inc/Client.h"
#include "../../inc/DefaultConsole.h"

namespace ConsoleArt
{
class ClientTools
{
private:
	SufuServer::Client client;
	std::string sharedString;
	ConsoleUtility::DefaultConsole console;
public:
	ClientTools();
	virtual ~ClientTools();
	void runClient();
	void handleResponse();
	void handleChat();
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_TOOLS_CLIENTTOOLS_H_ */
