//==============================================================================
// File       : ControllerSDL.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLE_ART_CONTROLLER_CONTROLLERSDL_H_
#define CONSOLE_ART_CONTROLLER_CONTROLLERSDL_H_

#include <iostream>
#include <atomic>

#include "../../console_art/controller/Controller.h"
#include "../../console_art/gui/sdl/AsciiPrinterSDL.h"
#include "../../console_art/gui/sdl/NotifierSDL.h"
#include "../../console_art/gui/sdl/StateManager.h"
#include "../../console_art/gui/sdl/WindowStates.hpp"
// SDL2
#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"
// consoleart
#include "component_sdl_lib/asset_tools/sprite_sheet_sdl.h"
#include "component_sdl_lib/base/state_sdl.h"

#include "../../embed/icon.h"


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
#endif /* CONSOLE_ART_CONTROLLER_CONTROLLERSDL_H_ */
