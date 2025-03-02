//==============================================================================
// File       : MainStateSDL.h
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Mar 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_MAINSTATE_H_
#define CONSOLEART_GUISDL_MAINSTATE_H_

#include <atomic>
#include <thread>
#include <string>

#include "../StateManager.h"
#include "../../controller/Controller.h"

#include "../../../sdl/abstract/StateSDL.h"
#include "../../../sdl/assets/StringSDL.h"
#include "../../../sdl/assets/SpriteSheetSDL.h"
#include "../../../sdl/components/ContentPanelSDL.h"
#include "../../../sdl/components/ImageButtonSDL.h"

#include "../../tools/ButtonBuilder.h"

namespace ConsoleArt
{
class MainStateSDL : public sdl::StateSDL
{
private:
	ButtonBuilder& buttons;
	sdl::StringSDL* selectedImageString;
	sdl::ContentPanelSDL* pane;
	TTF_Font* font;
	Controller& controller;
	StateManager& stateManager;
	std::atomic<bool> textUpdated;
	void addImageButtonEvent();
	bool updateString(sdl::StringSDL* stringSDL);
public:
	MainStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, StateManager& stateManager);
	virtual ~MainStateSDL();
	virtual void handleTick(SDL_Event &event) override;
	virtual void render() override;
	virtual void onReturn() override;
	virtual void onWindowResize() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_MAINSTATE_H_ */
