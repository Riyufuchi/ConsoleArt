//==============================================================================
// File       : AbstractAciiConversionMenu.cpp
// Author     : riyufuchi
// Created on : Mar 06, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../../console_art/abstract/AbstractAciiConversionState.h"

namespace consoleart {

AbstractAciiConversionState::AbstractAciiConversionState(Controller& controller, StateManager& stateManager) : AbstractState(controller, stateManager)
{
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::BASIC, "BASIC"});
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::BASIC_INVERTED, "BASIC INVERTED"});
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::PRECISE, "PRECISE"});
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::PRECISE_INVERTED, "PRECISE INVERTED"});
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::DETAILED, "DETAILED"});
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::DETAILED_INVERTED, "DETAILED INVERTED"});
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::SHADES, "SHADES"});
	texts.push_back({consoleartlib::AsciiConverter::CHAR_SETS::SHADES_INVERTED, "SHADES INVERTED"});
}

AbstractAciiConversionState::~AbstractAciiConversionState()
{
}

void AbstractAciiConversionState::convertImageEvent(consoleartlib::AsciiConverter::CHAR_SETS charSet)
{
	std::thread([asciiChar = charSet, this](){ controller.convertImage(controller.getSelectedImage(), asciiChar); }).detach();
}
} /* namespace consoleart */
