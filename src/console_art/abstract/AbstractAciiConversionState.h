//==============================================================================
// File       : AbstractAciiConversionMenu.h
// Author     : riyufuchi
// Created on : Mar 06, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLE_ART_ABSTRACT_ABSTRACTACIICONVERSIONSTATE_H_
#define CONSOLE_ART_ABSTRACT_ABSTRACTACIICONVERSIONSTATE_H_

#include "../../console_art/abstract/AbstractState.h"

namespace consoleart
{
class AbstractAciiConversionState : public AbstractState
{
protected:
	std::vector<std::pair<consoleartlib::AsciiConverter::CHAR_SETS, std::string>> texts;
	void convertImageEvent(consoleartlib::AsciiConverter::CHAR_SETS charSet);
public:
	AbstractAciiConversionState(Controller& controller, StateManager& stateManager);
	virtual ~AbstractAciiConversionState();
};

} /* namespace consoleart */

#endif /* CONSOLE_ART_ABSTRACT_ABSTRACTACIICONVERSIONSTATE_H_ */
