//==============================================================================
// File       : IMenu.h
// Author     : Riyufuchi
// Created on : Dec 19, 2023
// Last edit  : 28.12.2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: This interface specifies all menus that must be implemented
//==============================================================================

#ifndef CONSOLEART_INTERFACES_IMENU_HPP_
#define CONSOLEART_INTERFACES_IMENU_HPP_

#include "../../images/Image.h"

namespace ConsoleArt
{
class IMenu
{
public:
	virtual ~IMenu()
	{
	}
	virtual int charSetMenu() = 0;
	virtual int actionMenu() = 0;
	virtual int printMenu() = 0;
	virtual ConsoleUtils::Color colorPicker() = 0;
	virtual void displayImageInfo(Images::Image& image) = 0;
};
}
#endif /* CONSOLEART_INTERFACES_IMENU_HPP_ */
