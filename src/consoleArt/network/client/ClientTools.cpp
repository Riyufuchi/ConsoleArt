//==============================================================================
// File       : ClientTools.cpp
// Author     : Riyufuchi
// Created on : Mar 16, 2024
// Last edit  : Jan 20, 2025
// Copyright  : Copyright (c) 2024, Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ClientTools.h"

namespace ConsoleArt
{
ClientTools::ClientTools(ConsoleLib::IConsole& console) : ClientTools(console, "127.0.0.1")
{
}
ClientTools::ClientTools(ConsoleLib::IConsole& console, const char* ipAdress) : client(ipAdress, 6969), console(console), connection(true)
{
}
ClientTools::~ClientTools()
{
}
bool ClientTools::runClient()
{
	if (!client.isConnected())
	{
		console.err(client.getClientStatus());
		console.out("Can't connect to ConsoleArt server.\nStarted in off-line mode.\n\n");
		return false;
	}
	handleResponse();
	std::cin >> sharedString;
	client.sendRequest(sharedString);
	console.out(client.getClientStatus() + "\n");
	if (!client.isConnected())
	{
		console.err(client.getClientStatus());
		console.out("Can't connect to ConsoleArt server.\nStarted in off-line mode.\n\n");
		return false;
	}
	std::thread serverResponseThread(&ClientTools::handleChat, this);
	std::string command = "";
	while (command != "logout")
	{
		std::cin >> command;
		client.sendRequest(command);
	}
	connection = false;
	serverResponseThread.join();
	console.out("Press enter to exit... ");
	std::cin.get();
	std::cin.get();
	return true;
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
	while (connection)
	{
		if (client.listenForResponse(sharedString))
		{
			console.out("Server: " + sharedString + "\n");
		}
		else
			console.err("Server error : " + sharedString);
	}
	std::cout << "Chat session ended\n";
}
} /* namespace ConsoleArt */
