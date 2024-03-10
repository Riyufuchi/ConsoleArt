//============================================================================
// Name        : WindowsConsole
// Author      : Riyufuchi
// Created on  : 28.02.2024
// Last Edit   : Mar 4, 2024
//============================================================================

#ifdef _WIN32
#ifndef _WINDOWS_CONSOLE_H_
#define _WINDOWS_CONSOLE_H_

#include <iostream>
#include <windows.h>
#include <io.h>

#include "IConsole.hpp"

namespace ConsoleUtility
{
	class WindowsConsole : public IConsole
	{
	private:
		const int DEFAULT_COLOR_INDEX = 1;
		const int COLOR_TABLE_START_INDEX = 2;
		const int COLOR_TABLE_LENGHT = 16;
		int colorIndex = COLOR_TABLE_START_INDEX;
		Color defaultColor;
		HANDLE consoleHandle;
		CONSOLE_SCREEN_BUFFER_INFOEX consoleInfo;
	public:
		WindowsConsole();
		~WindowsConsole();
		void resetTextColor() override;
		void defaultTextColor() override;
		// Setters
		void setDefaultTextColor(Color color) override;
		void setTextColor(Color color) override;
		// Getters
		Color getDefaultTextColor() override;
		// Write methods
		void out(const char* text) override;
		void out(std::string text) override;
		void out(Color color, std::string text) override;
		void out(short int r, short int g, short int b, std::string text) override;
		void err(std::string text) override;
		void err(Color color, std::string text) override;
		void err(short int r, short int g, short int b, std::string text) override;
	};
}
#endif
#endif
