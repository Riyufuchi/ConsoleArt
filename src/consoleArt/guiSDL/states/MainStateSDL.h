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

#include "../../../sdl/abstract/StateSDL.h"
#include "../../../sdl/assets/StringSDL.h"
#include "../../../sdl/assets/SpriteSheetSDL.h"
#include "../../../sdl/components/ContentPanelSDL.h"
#include "../../../sdl/components/ImageButtonSDL.h"

#include "../../abstract/AbstractState.h"
#include "../../tools/ButtonBuilder.h"

namespace ConsoleArt
{
class MainStateSDL : public sdl::StateSDL, private AbstractState
{
private:
	ButtonBuilder& buttons;
	sdl::StringSDL* selectedImageString;
	sdl::ContentPanelSDL* pane;
	TTF_Font* font;
	std::atomic<bool> textUpdated;
	void addImageButtonEvent();
	bool updateString(sdl::StringSDL* stringSDL);
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
