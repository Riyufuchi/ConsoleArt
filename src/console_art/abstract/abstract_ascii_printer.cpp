//==============================================================================
// File       : AbstractAsciiPrinter.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "abstract_ascii_printer.h"

namespace consoleart
{
AbstractAsciiPrinter::AbstractAsciiPrinter() : AbstractAsciiPrinter(nullptr)
{
}

AbstractAsciiPrinter::AbstractAsciiPrinter(consoleartlib::AsciiConverter* converter) : converter(converter)
{
}

AbstractAsciiPrinter::~AbstractAsciiPrinter()
{
}

void AbstractAsciiPrinter::setTarget(consoleartlib::AsciiConverter* converter)
{
	this->converter = converter;
}

bool AbstractAsciiPrinter::printToFile(std::string& result)
{
	if (!converter)
	{
		result = "No target is set!";
		return false;
	}
	std::string fName = converter->getSourceImg().getFilepath();
	fName = fName.substr(0, fName.find_last_of('.')) + ".txt";
	std::fstream file(fName, std::ios::out | std::ios::trunc);
	if (!file)
	{
		result = "File IO error";
		return false;
	}
	const int HEIGHT = converter->getSourceImg().getImageInfo().height -1;
	if (converter->getSourceImg().isInverted())
		for(int i = HEIGHT; i >= 0; i--)
			file << converter->getLine(i) << "\n";
	else
		for(int i = 0; i < HEIGHT; i++)
			file << converter->getLine(i) << "\n";
	file.close();
	result = "File: " + fName + " was successfully created.";
	return true;
}
} /* namespace consoleart */
