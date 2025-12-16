//==============================================================================
// File       : AsciiPrinterCLI.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Mar 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_ASCIITOOLS_ASCIIPRINTERCLI_H_
#define CONSOLEART_ASCIITOOLS_ASCIIPRINTERCLI_H_

#include <locale>
#include <fstream>
#include <codecvt>
#include <iostream>

#include "../abstract/AbstractAsciiPrinter.h"
#include "IConsole.hpp"
#include "DataUtils.h"

namespace consoleart
{
class AsciiPrinterCLI : public AbstractAsciiPrinter
{
protected:
	consolelib::IConsole& console;
public:
	AsciiPrinterCLI(consolelib::IConsole& console);
	virtual ~AsciiPrinterCLI();
	virtual void printPixelColored() override;
	virtual void printToFile() override;
	virtual void printClassic() override;
	virtual void printCharColored() override;
};

} /* namespace consoleart */

#endif /* CONSOLEART_ASCIITOOLS_ASCIIPRINTERCLI_H_ */
