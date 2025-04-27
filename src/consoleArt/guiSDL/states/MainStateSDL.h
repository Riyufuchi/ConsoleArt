//==============================================================================
// File       : MainStateSDL.h
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Apr 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_MAINSTATE_H_
#define CONSOLEART_GUISDL_MAINSTATE_H_

#include <atomic>
#include <thread>
#include <string>

#include "../../../sdl/abstract/StateSDL.h"
#include "../../../sdl/assets/SpriteSheetSDL.h"
#include "../../../sdl/panels/ContentPanelSDL.h"
#include "../../../sdl/components/ImageButtonSDL.h"
#include "../../../sdl/components/LabelSDL.h"

#include "../../abstract/AbstractState.h"
#include "../../tools/ButtonBuilder.h"

namespace ConsoleArt
{
class MainStateSDL : public sdl::StateSDL, private AbstractState
{
private:
	ButtonBuilder& buttons;
	sdl::LabelSDL* selectedImageString;
	sdl::ContentPanelSDL* pane;
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
