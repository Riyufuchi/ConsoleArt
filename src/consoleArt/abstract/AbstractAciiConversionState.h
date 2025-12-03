//==============================================================================
// File       : AbstractAciiConversionMenu.h
// Author     : riyufuchi
// Created on : Mar 6, 2025
// Last edit  : May 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_ABSTRACT_ABSTRACTACIICONVERSIONSTATE_H_
#define CONSOLEART_ABSTRACT_ABSTRACTACIICONVERSIONSTATE_H_

#include "AbstractState.h"

namespace consoleart
{
class AbstractAciiConversionState : public AbstractState
{
protected:
	std::vector<std::pair<ImageUtils::AsciiConverter::CHAR_SETS, std::string>> texts;
	void convertImageEvent(ImageUtils::AsciiConverter::CHAR_SETS charSet);
public:
	AbstractAciiConversionState(Controller& controller, StateManager& stateManager);
	virtual ~AbstractAciiConversionState();
};

} /* namespace consoleart */

#endif /* CONSOLEART_ABSTRACT_ABSTRACTACIICONVERSIONSTATE_H_ */
