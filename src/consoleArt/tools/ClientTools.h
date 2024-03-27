//==============================================================================
// File       : ClientTools.h
// Author     : Riyufuchi
// Created on : Mar 16, 2024
// Last edit  : Mar 20, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _CONSOLEART_TOOLS_CLIENT_TOOLS_H_
#define _CONSOLEART_TOOLS_CLIENT_TOOLS_H_

#include <string>
#include <thread>

#include "IConsole.hpp"

#if defined(__linux__) || defined(__APPLE__)
	#include "UnixClient.h"
#elif defined(_WIN32)
	#include "WindowsClient.h"
#endif

namespace ConsoleArt
{
class ClientTools
{
private:
#if defined(__linux__) || defined(__APPLE__)
	SufuServer::UnixClient client;
#elif defined(_WIN32)
	SufuServer::WindowsClient client;
#endif
	std::string sharedString;
	ConsoleLib::IConsole& console;
	void handleResponse();
	void handleChat();
public:
	ClientTools(ConsoleLib::IConsole& console);
	ClientTools(ConsoleLib::IConsole& console, const char* ipAdress);
	virtual ~ClientTools();
	bool runClient();
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_TOOLS_CLIENTTOOLS_H_ */
