//==============================================================================
// File       : ServerTools.cpp
// Author     : Riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Mar 16, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ServerTools.h"

namespace ConsoleArt {

ServerTools::ServerTools() : server(6969)
{
	std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // Convert the time point to a time_t object
	std::tm* localTime = std::localtime(&currentTime); // Convert the time_t object to a struct tm object
	// Extract the year, month, and day from the struct tm object
	int year = localTime->tm_year + 1900; // tm_year is years since 1900
	int month = localTime->tm_mon + 1; // tm_mon is months since January (0-based)
	int day = localTime->tm_mday; // tm_mday is day of the month
	this->message = "Today is: " + std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year) + "\n";
}

ServerTools::~ServerTools() {
	// TODO Auto-generated destructor stub
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
	SufuServer::Client c; // Trigger server loop and shutdowns server
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
	console.out("On port: ");
	std::cout << server.getPort() << "\n";
	server.runServer();
}
} /* namespace ConsoleArt */
