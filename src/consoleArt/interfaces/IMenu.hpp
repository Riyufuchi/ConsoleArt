//==============================================================================
// File       : IMenu.h
// Author     : Riyufuchi
// Created on : Dec 19, 2023
// Last edit  : Mar 18, 2025
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
	enum Menu
	{
		MAIN_MENU,
		CHAR_SET_SELECTION,
		PRINT_OPTIONS,
		IMAGE_ACTION_OPTIONS,
		FILTERS,
		AFTER_PRINT_OPTIONS,
		MENU_COUNT
	};
	virtual ~IMenu() = default;
	virtual int charSetMenu() = 0;
	virtual int printMenu() = 0;
	virtual int imageEditOptions() = 0;
	virtual int imageFilterOptions() = 0;
	virtual int mainMenuOptions() = 0;
	virtual int afterPrintOptions() = 0;
	virtual ConsoleLib::Color colorPicker() = 0;
};
}
#endif /* CONSOLEART_INTERFACES_IMENU_HPP_ */
