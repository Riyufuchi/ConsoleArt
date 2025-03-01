//==============================================================================
// File       : MainStateSDL.h
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_MAINSTATE_H_
#define CONSOLEART_GUISDL_MAINSTATE_H_

#include <atomic>
#include <thread>
#include <string>

#include "../WindowStates.hpp"

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
	std::atomic<bool> textUpdated;
	void addImageButtonEvent();
	bool updateString(sdl::StringSDL* stringSDL);
public:
	MainStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, std::function<void()> switchState);
	virtual ~MainStateSDL();
	virtual void handleTick(SDL_Event &event) override;
	virtual void render() override;
	virtual void onReturn() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_MAINSTATE_H_ */
