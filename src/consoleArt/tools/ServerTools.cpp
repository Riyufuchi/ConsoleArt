//==============================================================================
// File       : ServerTools.cpp
// Author     : riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Mar 13, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ServerTools.h"

namespace ConsoleArt {

ServerTools::ServerTools() : server(6969)
{
	message = "ConsoleArt server v0.4\n";
}

ServerTools::~ServerTools() {
	// TODO Auto-generated destructor stub
}
void ServerTools::startServer()
{
	console.out(message);
	if (!server.isRunning())
	{
		console.err(server.getServerStatus());
		std::cin.get();
		return;
	}
	console.out(server.getServerStatus());
	console.out(" -> Server is up and running\n");
	console.out("On port: ");
	std::cout << server.getPort() << "\n";
	server.runServer(message);
	console.out(server.getServerStatus());
	console.out("Press enter to exit... ");
	std::cin.get();
}
} /* namespace ConsoleArt */
