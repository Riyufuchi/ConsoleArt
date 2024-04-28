//==============================================================================
// File       : IMenu.h
// Author     : Riyufuchi
// Created on : Dec 19, 2023
// Last edit  : Apr 28, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: This interface specifies all menus that must be implemented
//==============================================================================

#ifndef CONSOLEART_INTERFACES_IMENU_HPP_
#define CONSOLEART_INTERFACES_IMENU_HPP_

#include "../../images/Image.h"
#include "ColorUtils.h"

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
	virtual int handleMenu(int id) = 0;
	virtual ConsoleLib::Color colorPicker() = 0;
	virtual void displayImageInfo(Images::Image& image) = 0;
};
}
#endif /* CONSOLEART_INTERFACES_IMENU_HPP_ */
