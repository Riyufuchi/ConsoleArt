//==============================================================================
// File       : AsciiPrinterSDL.cpp
// Author     : riyufuchi
// Created on : Mar 4, 2025
// Last edit  : Mar 4, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "ascii_printer_sdl.h"

namespace consoleart
{

AsciiPrinterSDL::AsciiPrinterSDL(NotifierSDL* notifier) : AbstractAsciiPrinter(nullptr), notifier(notifier)
{
}

AsciiPrinterSDL::~AsciiPrinterSDL()
{
}


void AsciiPrinterSDL::printPixelColored()
{
}

void AsciiPrinterSDL::printToFile()
{
	std::string result;
	if (AbstractAsciiPrinter::printToFile(result))
		notifier->messageUser(AbstractNotifier::INFO, result);
	else
		notifier->messageUser(AbstractNotifier::PROBLEM, result);
}

void AsciiPrinterSDL::printClassic()
{
}

void AsciiPrinterSDL::printCharColored()
{
}
}
