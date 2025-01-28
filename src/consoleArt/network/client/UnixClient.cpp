//==============================================================================
// File       : UnixClient.cpp
// Author     : Riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Mar 27, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleLib
//==============================================================================

#include "UnixClient.h"

namespace ConsoleArt
{
	UnixClient::UnixClient() : UnixClient("127.0.0.1", 6969)
	{}
	UnixClient::UnixClient(const char* serverName, uint16_t port) : Client()
	{
		this->serverName = serverName;
		this->status = "OK";
		this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);

		if (clientSocket == -1)
		{
			status = "Error: Failed to create socket\n";
		}

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = inet_addr(serverName); // Server IP address
		serverAddr.sin_port = htons(port); // Server port

		// Set timeout for connect
		struct timeval timeout;
		timeout.tv_sec = 30; // Timeout in seconds
		timeout.tv_usec = 0;
		if (setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
		{
			std::cout << "30 sec";
			status = "Error: Failed to set socket option\n";
			disconnect();
			close(clientSocket);
		}

		if (connect(clientSocket, (sockaddr*) &serverAddr, sizeof(serverAddr)) == -1)
		{
			status = "Error: Connection failed\n";
			disconnect();
			close(clientSocket);
		}

		this->bytesSent = 0;
		this->totalSent = 0;
		this->messageLength = 0;

		// Initialize timeval struct for timeout
		messageTimeout.tv_sec = 60;
		messageTimeout.tv_usec = 0;
	}
	UnixClient::~UnixClient()
	{
		close(clientSocket);
	}
	void UnixClient::handleSendError() {
	    if (errno == EPIPE) {
	        status = "Connection closed by server\n";
	        disconnect();
	    } else {
	        status = "Error: Send failed (" + std::string(strerror(errno)) + ")\n";
	    }
	}
	bool UnixClient::sendRequest(std::string& message)
	{
	    size_t totalSent = 0;
	    uint32_t messageLength = htonl(message.length()); // Convert length to network byte order

	    // Send the length of the message (fixed 4 bytes)
	    ssize_t bytesSent = send(clientSocket, &messageLength, sizeof(messageLength), 0);
	    if (bytesSent == -1) {
	       handleSendError();
	        return false;
	    }

	    // Send the actual message
	    size_t messageLengthHost = message.length();
	    while (totalSent < messageLengthHost) {
	        bytesSent = send(clientSocket, message.c_str() + totalSent, messageLengthHost - totalSent, 0);
	        if (bytesSent == -1) {
	           handleSendError();
	            return false;
	        }
	        totalSent += bytesSent;
	    }

	    return true;
	}

	bool UnixClient::listenForResponse(std::string& response)
	{
		ssize_t bytesRead = recv(this->clientSocket, this->buffer, sizeof(this->buffer), 0);
		if (bytesRead == -1)
		{
			status = response = "Error: Receive failed - " + std::string(strerror(errno)) + "\n";
			return false;
		}
		else if (bytesRead == 0) // Server closed connection
		{
			status = response = "Server closed connection\n";
			disconnect();
			return false;
		}
		else // Data received
		{
			this->buffer[bytesRead] = '\0';
			response = std::string(this->buffer);
			return true;
		}
	}

	bool UnixClient::reciveMessage(std::string& message)
	{
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(this->clientSocket, &readfds);

		// Use select to wait for data on socket
		int result = select(this->clientSocket + 1, &readfds, NULL, NULL, &messageTimeout);
		if (result == -1)
		{
			status = message = "Error: Select failed - " + std::string(strerror(errno)) + "\n";
			return false;
		}
		else if (result == 0) // Timeout occurred
		{
			status = message = "Error: Receive timed out\n";
			return false;
		}
		else // Data is available on socket
		{
			ssize_t bytesRead = recv(this->clientSocket, this->buffer, sizeof(this->buffer), 0);
			if (bytesRead == -1)
			{
				status = message = "Error: Receive failed - " + std::string(strerror(errno)) + "\n";
				disconnect();
				return false;
			}
			else if (bytesRead == 0) // Server closed connection
			{
				status = message = "Server closed connection\n";
				disconnect();
				return false;
			}
			else // Data received
			{
				this->buffer[bytesRead] = '\0';
				message = std::string(this->buffer);
				return true;
			}
		}
	}

	bool UnixClient::listenForResponse(std::string& response, int timeout_ms)
	{
		response = "Error: Method not implemented!\n";
		return false;
	}
}
