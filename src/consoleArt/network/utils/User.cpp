//==============================================================================
// File       : User.cpp
// Author     : riyufuchi
// Created on : Jan 20, 2025
// Last edit  : Jan 20, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "User.h"

namespace ConsoleArt
{
User::User(const std::string username, int userSocket, bool connected) : name(username), userSocket(userSocket), connected(connected)
{
}
User::~User()
{
}
void User::disconnect()
{
	connected = false;
}
std::string User::getUsername() const
{
	return name;
}
int User::getUserSocket() const
{
	return userSocket;
}
bool User::isConnected() const
{
	return connected;
}
}
