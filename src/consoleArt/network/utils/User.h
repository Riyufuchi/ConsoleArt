//==============================================================================
// File       : User.h
// Author     : riyufuchi
// Created on : Jan 20, 2025
// Last edit  : Jan 20, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_NETWORK_USER_H_
#define CONSOLEART_NETWORK_USER_H_

#include <string>
#include <thread>
#include <utility> // for std::move
#include <atomic>

namespace ConsoleArt
{
class User
{
private:
	std::string name;
	int userSocket;
	std::atomic<bool> connected;
public:
	User(const std::string name, int userSocket, bool connected);
	~User();
	// Equality Operator
	bool operator==(const User& other) const
	{
		return name == other.name;
	}
	void disconnect();
	// Setters
	// Getters
	std::string getUsername() const;
	int getUserSocket() const;
	bool isConnected() const;
};
}
#endif
