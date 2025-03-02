//==============================================================================
// File       : AbstractAsciiPrinter.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_ABSTRACT_ABSTRACTASCIIPRINTER_H_
#define CONSOLEART_ABSTRACT_ABSTRACTASCIIPRINTER_H_

#include <string>

#include "../imageTools/AsciiConverter.h"

namespace ConsoleArt
{
class AbstractAsciiPrinter
{
protected:
	ImageUtils::AsciiConverter* converter;
	bool printToFile(std::string& result);
public:
	AbstractAsciiPrinter();
	AbstractAsciiPrinter(ImageUtils::AsciiConverter* converter);
	virtual ~AbstractAsciiPrinter();
	virtual void printClassic() = 0;
	virtual void printPixelColored() = 0;
	virtual void printCharColored() = 0;
	virtual void printToFile() = 0;
	void setTarget(ImageUtils::AsciiConverter* converter);
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_ABSTRACT_ABSTRACTASCIIPRINTER_H_ */
