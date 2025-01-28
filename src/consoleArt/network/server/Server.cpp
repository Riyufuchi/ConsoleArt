//==============================================================================
// File       : Server.cpp
// Author     : riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Jan 20, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: Simple server
//==============================================================================

#include "Server.h"

#if defined(__linux__) || defined(__APPLE__)
namespace ConsoleArt
{
	Server::Server() : Server(12345)
	{}
	Server::Server(uint16_t port) : Server(port, 255)
	{}
	Server::Server(uint16_t port, uint8_t maxUsers) : MAX_CONNECTED_USERS(maxUsers)
	{
		this->keepRunning = true;
		this->serverStatus = "OK";
		this->port = port;
		this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

		if (serverSocket == -1)
		{
			this->serverStatus = "Error: Failed to create socket\n";
			this->keepRunning = false;
		}

		int opt = 1;
		if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		{
			this->serverStatus = "Error: setsockopt failed";
			this->keepRunning = false;
		}

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(port); // Port number

		if (bind(serverSocket, (sockaddr*) &serverAddr, sizeof(serverAddr)) == -1)
		{
			this->serverStatus = "Error: Bind failed\n";
			close(serverSocket);
			this->keepRunning = false;
		}
		if (listen(serverSocket, SOMAXCONN) == -1)
		{
			this->serverStatus = "Error: Listen failed\n";
			close(serverSocket);
			this->keepRunning = false;
		}

		this->clientAddrLen = sizeof(clientAddr);
	}
	Server::~Server()
	{
		shutdownServer();
	}
	uint16_t Server::getPort()
	{
		return port;
	}
	std::string Server::getServerStatus()
	{
		return serverStatus;
	}
	bool Server::isRunning()
	{
		return serverStatus == "OK" && keepRunning;
	}
	void Server::shutdownServer()
	{
		std::cout << "Starting shutdown procedure\n";
		keepRunning = false;
		std::lock_guard<std::mutex> lock(usersMutex);
		if (users.empty())
			return;
		std::cout << "1/2 Notifying users.\n";
		int i = 1;
		for (std::shared_ptr<User> u : users)
		{
			std::cout << "Notifying user " << i << " of " << users.size() << "\n";
			sendResponse(u.get()->getUserSocket(), "Server is shutting down");
			u.get()->disconnect();
			clientThreadMap.at(u.get()->getUserSocket()).join();;
			close(u.get()->getUserSocket());
			i++;
		}
		std::cout << "2/2 Closing server socket.\n";
		close(serverSocket);
		users.clear();
		clientThreadMap.clear();
		std::cout << "Shutdown procedure completed!\n";
	}
	void Server::runServer()
	{
		clientAddrLen = sizeof(clientAddr);
		int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
		if (clientSocket == -1)
		{
			std::cerr << "Error: Accept failed" << std::endl;
			return;
		}
		// Handle communication with the client in a new thread
		std::lock_guard<std::mutex> lock(usersMutex);
		if (users.size() >= MAX_CONNECTED_USERS)
		{
			sendResponse(clientSocket, std::string("Server is full!"));
			close(clientSocket);
			return;
		}
		if (!keepRunning)
		{
			sendResponse(clientSocket, std::string("Server is shutting down! Connection no longer available!"));
			close(clientSocket);
			return;
		}
		std::string name = decodeClientMessage(clientSocket);
		users.push_back(std::make_shared<User>(name, clientSocket, true));
		std::lock_guard<std::mutex> lock2(clientThreadsMutex);
		clientThreadMap[clientSocket] = std::thread([this, userPtr = users.back().get()]()
		{
			this->handleUser(userPtr);
		});
		std::cout << "User " << name << " has joined" << " \n";
		sendResponse(clientSocket, std::string("Welcome ").append(name).append(" to ConsoleArt server"));
	}
	void Server::addUser(User* user)
	{
		std::lock_guard<std::mutex> lock(usersMutex);
		users.emplace_back(user);
	}
	void Server::showUsers()
	{
		std::lock_guard<std::mutex> lock(usersMutex);
		std::cout << users.size() << " / " << MAX_CONNECTED_USERS << "\n";
		std::cout << "Name | Connected\n";
		for (std::shared_ptr<User> u : users)
			std::cout << u.get()->getUsername() << " | " << (u.get()->isConnected() ? "Yes" : "No") << "\n";
	}
	bool Server::sendResponse(int clientSocket, std::string message)
	{
		if (send(clientSocket, message.c_str(), message.length(), 0) == -1)
		{
			this->serverStatus = "Error: Send failed\n";
			return false;
		}
		return true;
	}

	std::string Server::decodeClientMessage(int socket)
	{
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(socket, &readfds);

		struct timeval timeout;
		timeout.tv_sec = 10;  // Timeout after 10 seconds
		timeout.tv_usec = 0;

		int result = select(socket + 1, &readfds, nullptr, nullptr, &timeout);
		if (result > 0 && FD_ISSET(socket, &readfds))
		{
			uint32_t messageLength = 0;
			ssize_t bytesRead = recv(socket, &messageLength, sizeof(messageLength), MSG_WAITALL);
			if (bytesRead <= 0)
			{
				if (bytesRead == 0)
					std::cout << "Client disconnected.\n";
				else
					std::cout << "Client error: Failed to receive message length: "
							<< strerror(errno) << "\n";
				return "logout";
			}

			messageLength = ntohl(messageLength); // Convert to host byte order
			if (messageLength > 1024 * 1024) // Example: Limit to 1MB
			{
				std::cout << "Client error: Message length too large (" << messageLength << " bytes).\n";
				return "logout";
			}

			// Read the full message
			std::string message(messageLength, '\0');
			bytesRead = recv(socket, &message[0], messageLength, MSG_WAITALL);
			if (bytesRead <= 0)
			{
				if (bytesRead == 0)
					std::cout << "Client disconnected during message.\n";
				else
					std::cout << "Client error: Failed to receive full message: "
							<< strerror(errno) << "\n";
				return "logout";
			}

			return message;
		}
		else
		{
			if (result != 0)
				std::cout << "Client error: Select failed: " << strerror(errno) << "\n";
		}
		return "";
	}

	void Server::removeUser(const std::string& nameToRemove)
	{
		std::lock_guard<std::mutex> lock(usersMutex);
		users.erase(std::remove_if(users.begin(), users.end(),
		[&nameToRemove](std::shared_ptr<User> user)
		{
			if (user.get()->getUsername() == nameToRemove)
			{
				if (user.get()->isConnected())
				{
					user.get()->disconnect();
				}
				return true;
			}
			return false;
		}), users.end());
		if (users.empty())
		{
			std::cout << "Server is empty\n";
		}
	}
	void Server::handleUser(User* user)
	{
		while (user->isConnected())
		{
			std::string message = decodeClientMessage(user->getUserSocket());
			if (message == "logout")
			{
				sendResponse(user->getUserSocket(), "OK");
				user->disconnect();
			}
			if (!message.empty())
			{
				std::cout << "Received: " << message << " from " << user->getUsername() << std::endl;
				sendResponse(user->getUserSocket(), "OK");
			}
		}
		std::cout << "User " << user->getUsername() << " has disconnected." << std::endl;
	}
	int Server::getMaximumConnections() const
	{
		return MAX_CONNECTED_USERS;
	}
}
#endif
