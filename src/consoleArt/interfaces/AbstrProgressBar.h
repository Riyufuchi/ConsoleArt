//==============================================================================
// File       : AbstrProgressBar.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_INTERFACES_ABSTRPROGRESSBAR_H_
#define CONSOLEART_INTERFACES_ABSTRPROGRESSBAR_H_

namespace ConsoleArt
{
class AbstrProgressBar
{
protected:
	int maxStep;
	int currentStep;
public:
	AbstrProgressBar(int maxStep);
	virtual ~AbstrProgressBar();
	virtual void drawProgressBar() = 0;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_INTERFACES_ABSTRPROGRESSBAR_H_ */
