//==============================================================================
// File       : SelectImageStateSDL.h
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Apr 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_ABOUTSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_ABOUTSTATESDL_H_

#include <vector>
#include <memory>
#include <ranges>

#include "../../abstract/AbstractState.h"
#include "../../tools/ButtonBuilder.h"
#include "../../tools/GeneralTools.hpp"

#include "../../../sdl/components/LabelSDL.h"
#include "../../../sdl/panels/ContentPanelSDL.h"
#include "../../../sdl/assets/StringSDL.h"

namespace ConsoleArt
{
class AboutStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	const int SIZE = 36;
	const char* FONT = "assets/TF2professor.ttf";
	int y;
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL* pane;
public:
	AboutStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~AboutStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
