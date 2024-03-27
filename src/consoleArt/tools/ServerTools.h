//==============================================================================
// File       : ServerTools.h
// Author     : Riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Mar 27, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef _SERVER_TOOLS_H_
#define _SERVER_TOOLS_H_

#include <thread>

#include "ClientTools.h"

#include "../inc/TimeUtils.h"
#include "../inc/Server.h"
#include "../inc/UnixConsole.h"
#include "../inc/IConsole.hpp"

namespace ConsoleArt
{
class ServerTools
{
private:
	SufuServer::Server server;
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
