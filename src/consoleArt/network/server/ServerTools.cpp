//==============================================================================
// File       : ServerTools.cpp
// Author     : Riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Jan 20, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ServerTools.h"

namespace ConsoleArt
{
ServerTools::ServerTools() : server(6969, 2)
{
	ConsoleLib::Date today = ConsoleLib::TimeUtils::todaysDate();
	this->message = "Today is: " + std::to_string(today.day) + "." + std::to_string(today.month) + "." + std::to_string(today.year) + "\n";
}

ServerTools::~ServerTools()
{
}
void ServerTools::startServerThread()
{
	std::map<std::string, std::function<void()>> commandMap;
	commandMap["users"] = [&]() { server.showUsers(); };
	commandMap["status"] = [&]() { console.out(server.getServerStatus() + "\n"); };
	commandMap["kick"] = [&]() { server.removeUser("Riyu"); };
	commandMap["exit"] = [&]() { console.out("Activating shutdown command.\n"); server.shutdownServer(); };
	commandMap["help"] = []()
	{
		std::cout << "Available commands: exit, list users, status\n";
	};
	std::thread serverThread(&ServerTools::startServer, this);
	std::string command = "";
	while (server.isRunning())
	{
		std::cin >> command;
		auto it = commandMap.find(command);
		if (it != commandMap.end())
		{
			it->second(); // Call the associated function
		}
		else
		{
			std::cout << "Unknown command. Type 'help' for a list of commands.\n";
		}
	}
	ClientTools c(console);
	serverThread.join();
	console.out("Server exited with status: " + server.getServerStatus() + "\n");
	console.out("Press enter to exit... ");
	std::cin.get();
	std::cin.get();
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
	console.defaultTextColor();
	std::cout << "Port: " << server.getPort() << "\n";
	std::cout << "Maximum allowed users: " << server.getMaximumConnections() << "\n";
	console.resetTextColor();
	while (server.isRunning())
	{
		server.runServer();
	}
	console.out("Exiting server thread.\n");
}
} /* namespace ConsoleArt */
