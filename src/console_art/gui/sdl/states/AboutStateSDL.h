//==============================================================================
// File       : SelectImageStateSDL.h
// Author     : riyufuchi
// Created on : Mar 03, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_ABOUTSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_ABOUTSTATESDL_H_

#include <vector>
#include <memory>
#include <ranges>

#include "../../../../console_art/abstract/AbstractState.h"
#include "../../../../console_art/tools/ButtonBuilder.h"
#include "../../../../console_art/tools/config_sdl.hpp"
#include "../../../tools/general_tools.hpp"
#include "component_sdl_lib/components/label_sdl.h"
#include "component_sdl_lib/panels/content_panel_sdl.h"

namespace consoleart
{
class AboutStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	const int SIZE = 36;
	int y;
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL pane;
public:
	AboutStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~AboutStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace consoleart */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
