//==============================================================================
// File       : ServerTools.cpp
// Author     : Riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Mar 27, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ServerTools.h"

namespace ConsoleArt
{
ServerTools::ServerTools() : server(6969)
{
	DataUtility::Date today = DataUtility::TimeUtils::todaysDate();
	this->message = "Today is: " + std::to_string(today.day) + "." + std::to_string(today.month) + "." + std::to_string(today.year) + "\n";
}

ServerTools::~ServerTools()
{
}
void ServerTools::startServerThread()
{
	std::thread serverThread(&ServerTools::startServer, this);
	std::string command = "";
	while (command != "logout" && server.isRunning())
	{
		std::cin >> command;
	}
	server.shutdownServer();
	ClientTools c(console);
	//SufuServer::Client c; // Trigger server loop and shutdowns server
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
	console.out("Port: ");
	std::cout << server.getPort() << "\n";
	server.runServer();
}
} /* namespace ConsoleArt */
