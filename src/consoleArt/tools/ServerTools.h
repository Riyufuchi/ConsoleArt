//==============================================================================
// File       : ServerTools.h
// Author     : riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Mar 13, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_TOOLS_SERVERTOOLS_H_
#define CONSOLEART_TOOLS_SERVERTOOLS_H_

#include "../../inc/Server.h"
#include "../../inc/Client.h"
#include "../../inc/DefaultConsole.h"
#include "../../inc/IConsole.hpp"

namespace ConsoleArt
{
class ServerTools
{
private:
	SufuServer::Server server;
	std::string message;
	ConsoleUtility::DefaultConsole console;
public:
	ServerTools();
	virtual ~ServerTools();
	void startServer();
	static void clientDemo(ConsoleUtility::IConsole& console)
	{
		std::string msg = "Ping\a";
		SufuServer::Client client("127.0.0.1", 6969);
		if (!client.isConnected())
		{
			console.err(client.getClientStatus());
			console.out("Can't connect to ConsoleArt server.\nStarted in off-line mode.\n\n");
			return;
		}
		client.sendRequest(msg);
		client.sendRequest(msg);
		handleResponse(client, msg, console);
		client.sendRequest(msg = "Pong");
		handleResponse(client, msg, console);
		msg = "logout";
		client.sendRequest(msg);
		handleResponse(client, msg, console);
	}
	static void handleResponse(SufuServer::Client& client, std::string& msg, ConsoleUtility::IConsole& console)
	{
		if (client.listenForResponse(msg))
			console.out(msg + "\n");
		else
			console.err(msg);
	}
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_TOOLS_SERVERTOOLS_H_ */
