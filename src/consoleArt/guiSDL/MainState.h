//==============================================================================
// File       : MainState.h
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

#include "WindowStates.hpp"

#include "../sdl/abstract/StateSDL.h"
#include "../sdl/assets/StringSDL.h"
#include "../sdl/assets/SpriteSheetSDL.h"
#include "../sdl/components/ContentPanelSDL.h"
#include "../sdl/components/ImageButtonSDL.h"

#include "../tools/ButtonBuilder.h"

namespace ConsoleArt
{
class MainState : public StateSDL
{
private:
	ButtonBuilder& buttons;
	StringSDL* selectedImageString;
	ContentPanelSDL* pane;
	TTF_Font* font;
	std::function<bool(StringSDL*)> updateText;
	void addImageButtonEvent();
public:
	MainState(SDL_Renderer* renderer, WindowInfo& winInfo, ButtonBuilder& buttons, std::function<void()> addImageFunc, std::function<void()> addImageAsyncFunc,
			std::function<bool(StringSDL*)> updateText, std::function<void()> switchState);
	virtual ~MainState();
	virtual void handleTick(SDL_Event &event) override;
	virtual void render() override;
	virtual void onReturn() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_MAINSTATE_H_ */
