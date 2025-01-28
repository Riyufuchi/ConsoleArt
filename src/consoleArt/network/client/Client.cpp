//==============================================================================
// File       : Client.cpp
// Author     : Riyufuchi
// Created on : Mar 12, 2024
// Last edit  : Mar 27, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleLib
//==============================================================================

#include "Client.h"

namespace ConsoleArt
{
	Client::Client() : serverConnection(true), status("")
	{
	}
	void Client::disconnect()
	{
		serverConnection = false;
	}
	std::string Client::getClientStatus() const
	{
		return status;
	}
	bool Client::isConnected() const
	{
		return serverConnection;
	}
}
