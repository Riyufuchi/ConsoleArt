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
		std::cout << "Staring shutdown procedure\n";
		keepRunning = false;
		std::lock_guard<std::mutex> lock(usersMutex);
		std::cout << "1/3 Notifying users.\n";
		for (std::shared_ptr<User> u : users)
		{
			sendResponse(u.get()->getUserSocket(), "Server is shutting down");
			u.get()->disconnect();
		}
		std::cout << "2/3 Finishing users threads.\n";
		for (std::thread& t : clientThreads)
			t.join();
		std::cout << "3/3 Closing socket.\n";
		close(serverSocket);
		users.clear();
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
		sendResponse(clientSocket, "Username: ");
		std::string name = decodeClientMessage(clientSocket);
		users.push_back(std::make_shared<User>(name, clientSocket, true));
		std::lock_guard<std::mutex> lock2(clientThreadsMutex);
		clientThreads.emplace_back(&Server::handleUser, this, users.back().get());
		sendResponse(clientSocket, std::string("Welcome ").append(name).append(" to ConsoleArt server"));
		std::cout << "User " << name << " has joined" << " \n";
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
		char buffer[1024];
		ssize_t bytesRead = 0;

		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(socket, &readfds);

		struct timeval timeout;
		timeout.tv_sec = 3;  // Timeout after 5 seconds
		timeout.tv_usec = 0;

		int result = select(socket + 1, &readfds, nullptr, nullptr, &timeout);
		if (result > 0 && FD_ISSET(socket, &readfds))
		{
			bytesRead = recv(socket, buffer, sizeof(buffer), 0);
			if (bytesRead == -1)
			{
				std::cout << "Client error: Receive failed " << strerror(errno) << "\n";
				return "logout";
			}
			else if (bytesRead == 0)
			{
				return "logout";
			}
			buffer[bytesRead] = '\0';
			return std::string(buffer);
		}
		else
		{
			if (result == 0)
				return "";
			std::cout << "Client error: Select failed " << strerror(errno) << "\n";
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
				user->disconnect();
			if (!message.empty())
				std::cout << "Received: " << message << " from " << user->getUsername() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Avoid busy looping
		}
		std::cout << "User " << user->getUsername() << " has disconnected." << std::endl;
	}
	int Server::getMaximumConnections() const
	{
		return MAX_CONNECTED_USERS;
	}
}
#endif
