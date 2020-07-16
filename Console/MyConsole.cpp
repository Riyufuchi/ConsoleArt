#include "MyConsole.h"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <fstream>
#include <string>

/*
* Copyright Header
*
* Created On: 14.07.2020
* Last Edit: 16.07.2020
* Created By: Riyufuchi
*
*/

#ifndef UNICODE
#define UNICODE
#define _UNICODE
#endif

#define __STDC_LIB_EXT1__ 
#define __STDC_WANT_LIB_EXT1__ 1
#define _CRT_SECURE_NO_WARNINGS

//You need to have SLD installed  https://www.libsdl.org/download-2.0.php;
#ifdef _WIN32
//#pragma comment(lib, "Dll/SDL2.dll")
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#undef main

#pragma region EnumsEtc.
enum COLOUR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007,
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

#define KEY_OFFSET 256
#define VK_SPACE (SDLK_SPACE & 0xffff) + KEY_OFFSET
#define VK_BACK (SDLK_BACKSPACE & 0xffff) + KEY_OFFSET
#define VK_DELETE (SDLK_DELETE & 0xffff) + KEY_OFFSET
#define VK_HOME (SDLK_HOME & 0xffff) + KEY_OFFSET
#define VK_END (SDLK_END & 0xffff) + KEY_OFFSET
#define VK_RETURN (SDLK_RETURN & 0xffff) + KEY_OFFSET
#define VK_TAB (SDLK_TAB & 0xffff) + KEY_OFFSET
#define VK_INSERT (SDLK_INSERT & 0xffff) + KEY_OFFSET
#define VK_LSHIFT (SDLK_LSHIFT & 0xffff) + KEY_OFFSET
#define VK_RSHIFT (SDLK_RSHIFT & 0xffff) + KEY_OFFSET
#define VK_LCONTROL (SDLK_LCTRL & 0xffff) + KEY_OFFSET
#define VK_RCONTROL (SDLK_RCTRL & 0xffff) + KEY_OFFSET
#define VK_PRIOR (SDLK_PAGEUP & 0xffff)	+ KEY_OFFSET
#define VK_NEXT (SDLK_PAGEDOWN & 0xffff) + KEY_OFFSET
#define VK_ESCAPE (SDLK_ESCAPE & 0xffff) + KEY_OFFSET
#define VK_UP (SDLK_UP & 0xffff) + KEY_OFFSET
#define VK_DOWN	(SDLK_DOWN & 0xffff) + KEY_OFFSET
#define VK_LEFT (SDLK_LEFT & 0xffff) + KEY_OFFSET
#define VK_RIGHT (SDLK_RIGHT & 0xffff) + KEY_OFFSET
#define VK_F1 (SDLK_F1 & 0xffff) + KEY_OFFSET
#define VK_F2 (SDLK_F2 & 0xffff) + KEY_OFFSET
#define VK_F3 (SDLK_F3 & 0xffff) + KEY_OFFSET
#define VK_F4 (SDLK_F4 & 0xffff) + KEY_OFFSET
#define VK_F5 (SDLK_F5 & 0xffff) + KEY_OFFSET
#define VK_F6 (SDLK_F6 & 0xffff) + KEY_OFFSET
#define VK_F7 (SDLK_F7 & 0xffff) + KEY_OFFSET
#define VK_F8 (SDLK_F8 & 0xffff) + KEY_OFFSET
#define VK_F9 (SDLK_F9 & 0xffff) + KEY_OFFSET
#define VK_F10 (SDLK_F10 & 0xffff) + KEY_OFFSET
#define VK_F11 (SDLK_F11 & 0xffff) + KEY_OFFSET
#define VK_F12 (SDLK_F12 & 0xffff) + KEY_OFFSET
#define VK_MENU (SDLK_MENU & 0xffff) + KEY_OFFSET

enum PIXEL_TYPE
{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};

struct CHAR_INFO
{
	unsigned short glyph;
	short colour;
};

constexpr SDL_Color colour_lookup[] = 
{
	SDL_Color{ 0,0,0,255 },      // 0
	SDL_Color{ 0,0,127,255 },    // 1
	SDL_Color{ 0,127,0,255 },    // 2
	SDL_Color{ 0,127,127,255 },  // 3
	SDL_Color{ 127,0,0,255 },    // 4
	SDL_Color{ 127,0,127,255 },  // 5
	SDL_Color{ 127,127,0,255 },  // 6
	SDL_Color{ 192,192,192,255 },// 7
	SDL_Color{ 127,127,127,255 },// 8
	SDL_Color{ 0,0,255,255 },    // 9
	SDL_Color{ 0,255,0,255 },    // A
	SDL_Color{ 0,255,255,255 },  // B
	SDL_Color{ 255,0,0,255 },    // C
	SDL_Color{ 255,0,255,255 },  // D
	SDL_Color{ 255,255,0,255 },  // E
	SDL_Color{ 255,255,255,255 },// F
};
#pragma endregion
void MyConsole::test()
{
	std::cout << "MyConsole class test" << std::endl;
}
void MyConsole::setConsole()
{
}
/*
MyConsole::MyConsole()
{
}
MyConsole::~MyConsole()
{
}
*/

class ConsoleDisplay
{
protected:
	int screenWidth;
	int screenHeight;
	int fontWidth;
	int fontHeight;
	CHAR_INFO *bufScreen[2];
	int currentBuffer = 0;
	std::wstring appName;
	bool keyOldState[512] = { 0 };
	bool keyNewState[512] = { 0 };
	bool mouseOldState[5] = { 0 };
	bool mouseNewState[5] = { 0 };
	bool consoleInFocus = true;
	bool enableSound = false;
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;
	int mousePosX;
	int mousePosY;
	struct keyState
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	};
	struct keyStateWrap
	{
	keyState _state[512];
	keyState & operator[] (int nKeyID)
	{
		SDL_Keycode scode = (SDLK_UNKNOWN & 0xffff);
		if (nKeyID > KEY_OFFSET)
		{
			int scode = (SDL_Keycode)nKeyID - KEY_OFFSET;
			return _state[scode];
		}
		switch (nKeyID)
		{
			case L'A': scode = (SDLK_a & 0xffff); break;
			case L'B': scode = (SDLK_b & 0xffff); break;
			case L'C': scode = (SDLK_c & 0xffff); break;
			case L'D': scode = (SDLK_d & 0xffff); break;
			case L'E': scode = (SDLK_e & 0xffff); break;
			case L'F': scode = (SDLK_f & 0xffff); break;
			case L'G': scode = (SDLK_g & 0xffff); break;
			case L'H': scode = (SDLK_h & 0xffff); break;
			case L'I': scode = (SDLK_i & 0xffff); break;
			case L'J': scode = (SDLK_j & 0xffff); break;
			case L'K': scode = (SDLK_k & 0xffff); break;
			case L'L': scode = (SDLK_l & 0xffff); break;
			case L'M': scode = (SDLK_m & 0xffff); break;
			case L'N': scode = (SDLK_n & 0xffff); break;
			case L'O': scode = (SDLK_o & 0xffff); break;
			case L'P': scode = (SDLK_p & 0xffff); break;
			case L'Q': scode = (SDLK_q & 0xffff); break;
			case L'R': scode = (SDLK_r & 0xffff); break;
			case L'S': scode = (SDLK_s & 0xffff); break;
			case L'T': scode = (SDLK_t & 0xffff); break;
			case L'U': scode = (SDLK_u & 0xffff); break;
			case L'V': scode = (SDLK_v & 0xffff); break;
			case L'W': scode = (SDLK_w & 0xffff); break;
			case L'X': scode = (SDLK_x & 0xffff); break;
			case L'Y': scode = (SDLK_y & 0xffff); break;
			case L'Z': scode = (SDLK_z & 0xffff); break;
			case L'0': scode = (SDLK_0 & 0xffff); break;
			case L'1': scode = (SDLK_1 & 0xffff); break;
			case L'2': scode = (SDLK_2 & 0xffff); break;
			case L'3': scode = (SDLK_3 & 0xffff); break;
			case L'4': scode = (SDLK_4 & 0xffff); break;
			case L'5': scode = (SDLK_5 & 0xffff); break;
			case L'6': scode = (SDLK_6 & 0xffff); break;
			case L'7': scode = (SDLK_7 & 0xffff); break;
			case L'8': scode = (SDLK_8 & 0xffff); break;
			case L'9': scode = (SDLK_9 & 0xffff); break;
			/*
		    case L'\'': scode = (SDLK_APOSTROPHE & 0xffff); break;
			case L'\\': scode = (SDLK_BACKSLASH & 0xffff); break;
			case L',': scode = (SDLK_COMMA & 0xffff); break;
			case L'=': scode = (SDLK_EQUALS & 0xffff); break;
			case L'[': scode = (SDLK_LEFTBRACKET & 0xffff); break;
			case L']': scode = (SDLK_RIGHTBRACKET & 0xffff); break;
			case L'-': scode = (SDLK_MINUS & 0xffff); break;
			case L'.': scode = (SDLK_PERIOD & 0xffff); break;
			case L';': scode = (SDLK_SEMICOLON & 0xffff); break;
			case L'/': scode = (SDLK_SLASH & 0xffff); break;
			*/
		default: scode = (SDL_Keycode)nKeyID;
		}
		return _state[scode];
	}
} keys;
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture * screen;
	SDL_Texture* fontFile;
public:
	ConsoleDisplay()
	{
		screenWidth = 80;
		screenHeight = 30;
		memset(keyNewState, 0, 512 * sizeof(bool));
		memset(keyOldState, 0, 512 * sizeof(bool));
		memset(keys._state, 0, 512 * sizeof(keyState));
		mousePosX = 0;
		mousePosY = 0;
		appName = L"Default";
	}
	int ConstructConsole(int width, int height, int fontw, int fonth)
	{
		screenWidth = width;
		screenHeight = height;
		fontWidth = fontw;
		fontHeight = fonth;
		// Allocate memory for screen buffer
		bufScreen[0] = new CHAR_INFO[screenWidth*screenHeight];
		bufScreen[1] = new CHAR_INFO[screenWidth*screenHeight];
		// NOTE(MrBadNewS): set buffers to zero, old way
		memset(bufScreen[0], 0, screenWidth*screenHeight * sizeof(CHAR_INFO));
		memset(bufScreen[1], 0, screenWidth*screenHeight * sizeof(CHAR_INFO));
		currentBuffer = 0;
		return 1;
	}
};