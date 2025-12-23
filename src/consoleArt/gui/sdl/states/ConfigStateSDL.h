//==============================================================================
// File       : ConfigStateSDL.h
// Author     : riyufuchi
// Created on : Nov 16, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_CONFIGSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_CONFIGSTATESDL_H_

#include <vector>
#include <memory>
#include <ranges>

#include "../../../abstract/AbstractState.h"
#include "../../../tools/ButtonBuilder.h"
#include "../../../tools/general_tools.hpp"
#include "../../../tools/config_sdl.hpp"

#include "LabelSDL.h"
#include "ContentPanelSDL.h"

namespace consoleart
{
class ConfigStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	const int SIZE = 36;
	int y;
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL pane;
public:
	ConfigStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~ConfigStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace consoleart */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
