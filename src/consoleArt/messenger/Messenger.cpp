//==============================================================================
// File       : Messenger.cpp
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : Jan 14, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "Messenger.h"

namespace ConsoleArt
{

Messenger::Messenger()
{
}

Messenger::~Messenger()
{
}

void Messenger::messageUser(std::string message)
{
	messageUser(MessageType::INFO, message);
}

} /* namespace ConsoleArt */
