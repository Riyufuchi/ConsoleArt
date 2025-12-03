//==============================================================================
// File       : Messenger.cpp
// Author     : riyufuchi
// Created on : Apr 28, 2024
// Last edit  : May 16, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: consoleart
//==============================================================================

#include "AbstractNotifier.h"

namespace consoleart
{

AbstractNotifier::AbstractNotifier()
{
}

AbstractNotifier::~AbstractNotifier()
{
}

void AbstractNotifier::messageUser(const std::string& message)
{
	messageUser(MessageType::INFO, message);
}

} /* namespace consoleart */
