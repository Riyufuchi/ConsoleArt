//==============================================================================
// File       : NotifierSDL.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : May 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "NotifierSDL.h"

namespace ConsoleArt
{

NotifierSDL::NotifierSDL() : NotifierTFD()
{

}

NotifierSDL::~NotifierSDL()
{
}

void NotifierSDL::displayImageInfo(const Images::Image& image)
{
	std::thread([this, &image]()
	{
		NotifierTFD::displayImageInfo(image);
	}).detach(); // Shows the dialog (blocking, but running in another thread)
}

void NotifierSDL::messageUser(AbstractNotifier::MessageType messageSeverity, const std::string& message)
{
	std::thread([this, messageSeverity, message]()
	{
		NotifierTFD::messageUser(messageSeverity, message);
	}).detach();
}

} /* namespace ConsoleArt */
