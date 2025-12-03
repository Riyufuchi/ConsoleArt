//==============================================================================
// File       : NotifierTFD.h
// Author     : riyufuchi
// Created on : May 16, 2025
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_TINYFILEDIALOGS_NOTIFIERTFD_H_
#define CONSOLEART_TINYFILEDIALOGS_NOTIFIERTFD_H_

#include "../../abstract/AbstractNotifier.h"
#include "DataUtils.h"

extern "C"
{
	#include "../../../include/tinyfiledialogs.h"
}

namespace consoleart
{
class NotifierTFD : public AbstractNotifier
{
public:
	NotifierTFD();
	~NotifierTFD();
	virtual void displayImageInfo(const consoleartlib::Image &image) override;
	virtual void messageUser(MessageType messageSeverity, const std::string& message) override;
};

} /* namespace consoleart */

#endif /* CONSOLEART_GUISDL_NOTIFIERSDL_H_ */
