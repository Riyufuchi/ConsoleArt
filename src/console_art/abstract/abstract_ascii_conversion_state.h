//==============================================================================
// File       : AbstractAciiConversionMenu.h
// Author     : riyufuchi
// Created on : Mar 06, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLE_ART_ABSTRACT_ABSTRACT_ASCII_CONVERSION_STATE_H_
#define CONSOLE_ART_ABSTRACT_ABSTRACT_ASCII_CONVERSION_STATE_H_

#include "abstract_state.h"

namespace consoleart
{
class AbstractAsciiConversionState : public AbstractState
{
protected:
	std::vector<std::pair<consoleartlib::AsciiConverter::CHAR_SETS, std::string>> texts;
	void convertImageEvent(consoleartlib::AsciiConverter::CHAR_SETS charSet);
public:
	AbstractAsciiConversionState(Controller& controller, StateManager& stateManager);
	virtual ~AbstractAsciiConversionState();
};

} /* namespace consoleart */

#endif /* CONSOLE_ART_ABSTRACT_ABSTRACT_ASCII_CONVERSION_STATE_H_ */
