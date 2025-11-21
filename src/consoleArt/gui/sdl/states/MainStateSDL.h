//==============================================================================
// File       : MainStateSDL.h
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_MAINSTATE_H_
#define CONSOLEART_GUISDL_MAINSTATE_H_

#include <atomic>
#include <thread>
#include <string>

#include "StateSDL.h"
#include "SpriteSheetSDL.h"
#include "ContentPanelSDL.h"
#include "ImageButtonSDL.h"
#include "LabelSDL.h"

#include "../../../abstract/AbstractState.h"
#include "../../../tools/ButtonBuilder.h"
#include "../../../tools/ConfigSDL.hpp"

namespace ConsoleArt
{
class MainStateSDL : public sdl::StateSDL, private AbstractState
{
private:
	ButtonBuilder& buttons;
	sdl::LabelSDL* selectedImageString;
	sdl::ContentPanelSDL pane;
	std::atomic<bool> textUpdated;
	void addImageButtonEvent();
	bool updateString(sdl::LabelSDL* stringSDL);
public:
	MainStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, StateManager& stateManager);
	virtual ~MainStateSDL();
	void loadDropedFile(char* droppedFile);
	virtual void handleTick(SDL_Event &event) override;
	virtual void render() override;
	virtual void onReturn() override;
	virtual void onWindowResize() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_MAINSTATE_H_ */
