//==============================================================================
// File       : ControllerSDL.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Dec 03, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_CONTROLLER_CONTROLLERSDL_H_
#define CONSOLEART_CONTROLLER_CONTROLLERSDL_H_

#include <iostream>
#include <atomic>
// SDL2
#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"
// consoleart
#include "Controller.h"
#include "../gui/sdl/NotifierSDL.h"
#include "../gui/sdl/AsciiPrinterSDL.h"
#include "SpriteSheetSDL.h"
#include "StateSDL.h"

#include "../../embed/icon.h"
#include "../gui/sdl/StateManager.h"
#include "../gui/sdl/WindowStates.hpp"


extern "C"
{
	#include "../../include/tinyfiledialogs.h"
}

namespace consoleart
{
class ControllerSDL : public Controller
{
private:
	int width, height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	StateManager* stateManager;
	sdl::WindowInfo winInfo;
	sdl::StateSDL* currentState;
	ButtonBuilder* buttons;
	SDL_Event event;
	void setAppIcon();
protected:
	virtual IndexDataType selectImageMenu() override;
	virtual void showAboutApplicationInfo() override;
	virtual std::string inputImageName() override;
public:
	ControllerSDL();
	~ControllerSDL();
	virtual void run() override;
};
} /* namespace consoleart */
#endif /* CONSOLEART_CONTROLLER_CONTROLLERSDL_H_ */
