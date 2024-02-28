//============================================================================
// Name        : WindowsConsole
// Author      : Riyufuchi
// Created on  : 28.02.2024
// Last Edit   : 28.02.2024
//============================================================================

#ifdef _WIN32
#ifndef _WINDOWS_CONSOLE_H_
#define _WINDOWS_CONSOLE_H_

#include <iostream>
#include <windows.h>
//#include <fcntl.h>
#include <io.h>

#include "IConsole.hpp"

namespace ConsoleUtils
{
	class WindowsConsole : public IConsole
	{
	private:
		const int TEMP_COLOR_INDEX = 4;
		const int DEFAULT_COLOR_INDEX = 3;
		const int CURRENT_COLOR_INDEX = 2;
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
