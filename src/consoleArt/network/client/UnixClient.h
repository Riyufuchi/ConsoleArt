//==============================================================================
// File       : UnixClient.h
// Author     : riyufuchi
// Created on : Mar 11, 2024
// Last edit  : Mar 20, 2024
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleLib
//==============================================================================

#if defined(__linux__) || defined(__APPLE__)

#ifndef _UNIX_CLIENT_H_
#define _UNIX_CLIENT_H_

#include <iostream>
#include <string>
#include <cstring>

#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Client.h"


namespace ConsoleArt
{
class UnixClient : public Client
{
private:
	const char* serverName;
	ssize_t bytesSent;
	size_t totalSent;
	size_t messageLength;
	int clientSocket;
	sockaddr_in serverAddr;
	char buffer[1024];
	struct timeval messageTimeout;
public:
	UnixClient();
	UnixClient(const char* serverName, uint16_t port);
	~UnixClient();
	void handleSendError();
	bool sendRequest(std::string& message) override;
	bool listenForResponse(std::string& message) override;
	bool listenForResponse(std::string& message, int timeout_ms) override;
	bool reciveMessage(std::string& message) override;
};
}
#endif /* _SERVER_H_ */
#endif
