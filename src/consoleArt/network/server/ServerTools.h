//==============================================================================
// File       : ServerTools.h
// Author     : Riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Jan 20, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _SERVER_TOOLS_H_
#define _SERVER_TOOLS_H_

#include <thread>
#include <map>
#include <functional>

#include "../client/ClientTools.h"

#include "../inc/TimeUtils.h"
#include "Server.h"
#include "../inc/UnixConsole.h"
#include "../inc/IConsole.hpp"

namespace ConsoleArt
{
class ServerTools
{
private:
	ConsoleArt::Server server;
	std::string message;
	ConsoleLib::UnixConsole console;
	void startServer();
public:
	ServerTools();
	virtual ~ServerTools();
	void startServerThread();
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_TOOLS_SERVERTOOLS_H_ */
