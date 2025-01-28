//==============================================================================
// File       : Server.h
// Author     : riyufuchi
// Created on : Mar 11, 2024
// Last edit  : Jan 20, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: Simple server
//==============================================================================

#ifndef _SERVER_H_
#define _SERVER_H_

#if defined(__linux__) || defined(__APPLE__)

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <thread> // for std::thread
#include <vector> // for std::vecto
#include <mutex>
#include <algorithm>
#include <memory>
#include <map>

#include "../utils/User.h"

namespace ConsoleArt
{
class Server
{
private:
	const size_t MAX_CONNECTED_USERS;
	int serverSocket;
	sockaddr_in serverAddr;
	sockaddr_in clientAddr;
	socklen_t clientAddrLen;
	bool keepRunning;
	std::string serverStatus, temporaryString;
	uint16_t port;
	std::vector<std::shared_ptr<User>> users;
	std::mutex usersMutex;
	std::map<int, std::thread> clientThreadMap;
	std::mutex clientThreadsMutex;
	// Methods
	void handleUser(User* user); // Function to handle communication with a single user
	void addUser(User* user);
	// Functions
	bool sendResponse(int clientSocket, std::string message);
	std::string decodeClientMessage(int clientSocket);
public:
	Server();
	Server(uint16_t port);
	Server(uint16_t port, uint8_t maxUsers);
	~Server();
	void runServer();
	void shutdownServer();
	void showUsers();
	// Functions
	void removeUser(const std::string& nameToRemove);
	bool isRunning();
	uint16_t getPort();
	std::string getServerStatus();
	int getMaximumConnections() const;
};
}
#endif
#endif /* _SERVER_H_ */
