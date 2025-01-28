//==============================================================================
// File       : WindowsClient.h
// Author     : Riyufuchi
// Created on : Mar 11, 2024
// Last edit  : Mar 16, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: Simple client
//==============================================================================

#if defined(_WIN32)

#ifndef _WINDOWS_CLIENT_H_
#define _WINDOWS_CLIENT_H_

#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>

#include "Client.h"

#pragma comment(lib, "Ws2_32.lib") // Link against Ws2_32.lib library

namespace SufuServer
{
class WindowsClient : public Client
{
private:
	SOCKET clientSocket = INVALID_SOCKET;
	sockaddr_in serverAddr;
	char buffer[1024];
	const char* serverName;
	std::string status;
public:
	WindowsClient();
	WindowsClient(const char* serverName, uint16_t port);
	~WindowsClient();
	bool sendRequest(std::string& message) override;
	bool listenForResponse(std::string& message) override;
	bool listenForResponse(std::string& message, int timeout_ms) override;
};
}
#endif /* _SERVER_H_ */
