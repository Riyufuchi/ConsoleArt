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
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <thread>

#include "Controller.h"
#include "../guiSDL/NotifierSDL.h"
#include "../gui/assets/SpriteSheet.h"
#include "../gui/assets/StringPrinter.h"
#include "../gui/components/ButtonSDL.h"
#include "../gui/components/ImageButtonSDL.h"
#include "../gui/components/ContentPanelSDL.h"

#include "../../include/tinyfiledialogs.h"

namespace ConsoleArt
{
class ControllerSDL : public Controller
{
private:
	int width, height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Color backgroundColor {80, 80, 80, 255};
	StringPrinter* mainFont;
	SpriteSheet* sheet;
	ContentPanelSDL* pane;
	void addImageButtonEvent();
protected:
	virtual void showAboutApplicationInfo() override;
	virtual std::string inputImageName() override;
	virtual Images::Image* selectImage() override;
	virtual void refreshMenu() override;
public:
	ControllerSDL();
	~ControllerSDL();
	virtual void run() override;
	virtual void configure(std::map<std::string, std::vector<std::string>>& config) override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_CONTROLLER_CONTROLLERSDL_H_ */
