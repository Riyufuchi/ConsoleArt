//==============================================================================
// File       : AsciiPrinterSDL.h
// Author     : riyufuchi
// Created on : Mar 4, 2025
// Last edit  : Mar 4, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_ASCIIPRINTERSDL_H_
#define CONSOLEART_GUISDL_ASCIIPRINTERSDL_H_

#include "../abstract/AbstractAsciiPrinter.h"
#include "NotifierSDL.h"

namespace ConsoleArt
{
class AsciiPrinterSDL: public AbstractAsciiPrinter
{
private:
	NotifierSDL* notifier;
public:
	AsciiPrinterSDL(NotifierSDL* notifier);
	virtual ~AsciiPrinterSDL();
	virtual void printPixelColored() override;
	virtual void printToFile() override;
	virtual void printClassic() override;
	virtual void printCharColored() override;
};

} /* namespace sdl */

#endif /* CONSOLEART_GUISDL_ASCIIPRINTERSDL_H_ */
