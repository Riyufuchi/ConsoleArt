//==============================================================================
// File       : AbstractAsciiPrinter.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLE_ART_ABSTRACT_ABSTRACTASCIIPRINTER_H_
#define CONSOLE_ART_ABSTRACT_ABSTRACTASCIIPRINTER_H_

#include <string>

#include "consoleartlib/image_tools/ascii_converter.h"

namespace consoleart
{
class AbstractAsciiPrinter
{
protected:
	consoleartlib::AsciiConverter* converter;
	bool printToFile(std::string& result);
public:
	AbstractAsciiPrinter();
	AbstractAsciiPrinter(consoleartlib::AsciiConverter* converter);
	virtual ~AbstractAsciiPrinter();
	virtual void printClassic() = 0;
	virtual void printPixelColored() = 0;
	virtual void printCharColored() = 0;
	virtual void printToFile() = 0;
	void setTarget(consoleartlib::AsciiConverter* converter);
};
} /* namespace consoleart */
#endif /* CONSOLE_ART_ABSTRACT_ABSTRACTASCIIPRINTER_H_ */
