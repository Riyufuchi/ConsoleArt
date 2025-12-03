//==============================================================================
// File       : AbstrProgressBar.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_INTERFACES_ABSTRACTPROGRESSBAR_H_
#define CONSOLEART_INTERFACES_ABSTRACTPROGRESSBAR_H_

namespace consoleart
{
class AbstractProgressBar
{
protected:
	int maxStep;
	int currentStep;
public:
	AbstractProgressBar(int maxStep);
	virtual ~AbstractProgressBar();
	virtual void drawProgressBar() = 0;
};

} /* namespace consoleart */

#endif /* CONSOLEART_INTERFACES_ABSTRPROGRESSBAR_H_ */
