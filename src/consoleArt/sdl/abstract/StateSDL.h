//==============================================================================
// File       : StateSDL.h
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Feb 26, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_SDL_ABSTRACT_STATESDL_H_
#define CONSOLEART_SDL_ABSTRACT_STATESDL_H_

#include <SDL2/SDL.h>

#include "../../abstract/AbstrctState.h"

namespace ConsoleArt
{
struct WindowInfo
{
	int w;
	int h;
	int mouseX;
	int mouseY;
	bool keepRunning;
};
class StateSDL : public AbstrctState
{
protected:
	SDL_Color backgroundColor {80, 80, 80, 255};
	SDL_Renderer* renderer;
	WindowInfo& winInfo;
public:
	StateSDL(SDL_Renderer* renderer, StateController& controller, WindowInfo& winInfo);
	virtual ~StateSDL();
	void exitApplication();
	virtual void handleTick(SDL_Event& event) = 0;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_SDL_ABSTRACT_STATESDL_H_ */
