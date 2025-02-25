//==============================================================================
// File       : ControllerSDL.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLER_CONTROLLERSDL_H_
#define CONSOLEART_CONTROLLER_CONTROLLERSDL_H_

#include <SDL2/SDL.h>
#include <iostream>

#include "ControllerZenity.h"
#include "../gui/components/ButtonSDL.h"
#include "../gui/components/ImageButtonSDL.h"
#include "../gui/assets/SpriteSheet.h"
#include "../gui/components/ContentPanelSDL.h"

namespace ConsoleArt
{
class ControllerSDL : public ControllerZenity
{
private:
	int width, height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Color backgroundColor {80, 80, 80, 255};
	SpriteSheet* sheet;
	ContentPanelSDL* pane;
protected:
	virtual void showAboutApplicationInfo() override;
public:
	ControllerSDL(ConsoleLib::UnixConsole& console);
	~ControllerSDL();
	virtual void run() override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_CONTROLLER_CONTROLLERSDL_H_ */
