//==============================================================================
// File       : ControllerSDL.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLER_CONTROLLERSDL_H_
#define CONSOLEART_CONTROLLER_CONTROLLERSDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <thread>
#include <atomic>

#include "Controller.h"
#include "../guiSDL/NotifierSDL.h"
#include "../sdl/assets/SpriteSheetSDL.h"
#include "../sdl/assets/StringSDL.h"
#include "../sdl/components/ButtonSDL.h"
#include "../sdl/components/ContentPanelSDL.h"
#include "../sdl/components/ImageButtonSDL.h"
#include "../sdl/abstract/StateSDL.h"
#include "../guiSDL/MainState.h"

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
	WindowInfo winInfo;
	StateSDL* currentState;
	std::atomic<bool> textUpdated;
	void addImageButtonEvent();
	std::atomic<bool> getTextUpdated();
	bool updateString(StringSDL* stringSDL);
protected:
	virtual Images::Image* selectImage() override;
	virtual void showAboutApplicationInfo() override;
	virtual std::string inputImageName() override;
public:
	ControllerSDL();
	~ControllerSDL();
	virtual void run() override;
	virtual void configure(std::map<std::string, std::vector<std::string>>& config) override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_CONTROLLER_CONTROLLERSDL_H_ */
