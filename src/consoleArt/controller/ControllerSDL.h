//==============================================================================
// File       : ControllerSDL.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Nov 17, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLER_CONTROLLERSDL_H_
#define CONSOLEART_CONTROLLER_CONTROLLERSDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <atomic>

#include "Controller.h"
#include "../guiSDL/NotifierSDL.h"
#include "../guiSDL/AsciiPrinterSDL.h"
#include "SpriteSheetSDL.h"
#include "StringSDL.h"
#include "StateSDL.h"

#include "../../embed/icon.h"
#include "../guiSDL/StateManager.h"
#include "../guiSDL/WindowStates.hpp"


extern "C"
{
	#include "../../include/tinyfiledialogs.h"
}

namespace ConsoleArt
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
	void setAppIcon(std::string iconPath);
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
} /* namespace ConsoleArt */
#endif /* CONSOLEART_CONTROLLER_CONTROLLERSDL_H_ */
