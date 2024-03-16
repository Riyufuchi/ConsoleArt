//==============================================================================
// File       : ClientTools.cpp
// Author     : riyufuchi
// Created on : Mar 16, 2024
// Last edit  : Mar 16, 2024
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ClientTools.h"

namespace ConsoleArt
{
ClientTools::ClientTools() : client("127.0.0.1", 6969)
{
}
ClientTools::~ClientTools()
{
	// TODO Auto-generated destructor stub
}
void ClientTools::runClient()
{
	if (!client.isConnected())
	{
		console.err(client.getClientStatus());
		console.out("Can't connect to ConsoleArt server.\nStarted in off-line mode.\n\n");
		return;
	}
	console.out("Username: ");
	std::cin >> sharedString;
	client.sendRequest(sharedString);
	handleResponse();
	console.out(client.getClientStatus() + "\n");
	if (!client.isConnected())
	{
		console.err(client.getClientStatus());
		console.out("Can't connect to ConsoleArt server.\nStarted in off-line mode.\n\n");
		console.out("Press enter to exit... ");
		std::cin.get();
		std::cin.get();
		return;
	}
	std::string command = "";
	std::thread serverResponseThread(&ClientTools::handleChat, this);
	while (command != "logout")
	{
		std::cin >> command;
		client.sendRequest(command);
	}
	serverResponseThread.join();
	console.out("Press enter to exit... ");
	std::cin.get();
	std::cin.get();
}
void ClientTools::handleResponse()
{
	if (client.listenForResponse(sharedString, 5000))
		console.out(sharedString + "\n");
	else
		console.err(sharedString);
}
void ClientTools::handleChat()
{
	while (client.isConnected())
	{
		if (client.listenForResponse(sharedString))
		{
			console.out("\nServer: " + sharedString + "\n");
		}
		else
			console.err("Server error : " + sharedString);
	}
	std::cout << "Chat session ended\n";
}
} /* namespace ConsoleArt */
