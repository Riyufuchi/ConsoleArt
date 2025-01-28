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
ClientTools::ClientTools(ConsoleLib::IConsole& console, const char* ipAdress) : client(ipAdress, 6969), console(console), messageOK(false)
{
	std::cout << "Username: ";
	std::getline(std::cin, sharedString);
}
ClientTools::~ClientTools()
{
}
bool ClientTools::connectClient()
{
	if (!client.isConnected() || client.getClientStatus() != "OK")
	{
		console.out("Can't connect to ConsoleArt server.\nStarted in off-line mode.\n");
		return false;
	}
	client.sendRequest(sharedString);
	if (!client.isConnected() || client.getClientStatus() != "OK")
	{
		console.out("Can't connect to ConsoleArt server.\nClient status: " + client.getClientStatus() + "\nStarted in off-line mode.\n");
		return false;
	}
	return true;
}
bool ClientTools::runClient()
{
	std::map<std::string, std::function<void()>> commandMap;
	commandMap["status"] = [&]() { console.out(client.getClientStatus() + "\n"); };
	commandMap["logout"] = [&]()
	{
		std::string com = "logout";
		client.sendRequest(com);
		client.disconnect();
	};
	commandMap["exit"] = [&]()
	{
		std::string com = "logout";
		client.sendRequest(com);
		client.disconnect();
	};
	commandMap["help"] = []() { std::cout << "Available commands: exit, logout, status\n"; };
	std::thread serverResponseThread(&ClientTools::handleChat, this);
	std::string command = "";
	int errors = 0;
	while (client)
	{
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, command);
		auto it = commandMap.find(command);
		if (it != commandMap.end())
		{
			it->second(); // Call the associated function
		}
		else
		{
			client.sendRequest(command);
			std::lock_guard<std::mutex> lock(tokenMutex);
			messageOK = false;
			while (!messageOK)
			{
				if (errors >= 10)
				{
					if (ConsoleLib::ConsoleUtils::yesNo("Terminate connection? [Y/n]"))
					{
						client.disconnect();
						messageOK = true;
					}
					else
						errors = 0;
				}
				errors++;
				console.out("Sending failed - try " + std::to_string(errors) +  " of 10\n");
				client.sendRequest(command);
			}
		}
	}
	console.out("Waiting for response thread...\n");
	serverResponseThread.join();
	console.out("Press enter to exit...\n");
	std::cin.get();
	std::cin.get();
	return true;
}
void ClientTools::handleChat()
{
	int errors = 0;
	while (client)
	{
		if (client.reciveMessage(sharedString))
		{
			console.out("Server: " + sharedString + "\n");
			std::lock_guard<std::mutex> lock(tokenMutex);
			if (sharedString == "OK")
				messageOK = true;
		}
		else
		{
			console.err("Server error : " + sharedString);
			if (errors >= 10)
			{
				if (ConsoleLib::ConsoleUtils::yesNo("Terminate connection? [Y/n]"))
					client.disconnect();
				else
					errors = 0;
			}
			errors++;
		}
	}
	std::cout << "Chat session ended\n";
	client.disconnect();
}
} /* namespace ConsoleArt */
