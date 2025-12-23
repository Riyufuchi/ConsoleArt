//==============================================================================
// File       : SelectImageStateSDL.h
// Author     : riyufuchi
// Created on : Mar 03, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_ASCIICONVERTSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_ASCIICONVERTSTATESDL_H_

#include <vector>
#include <memory>
#include <future>

#include "../../../../console_art/abstract/AbstractAciiConversionState.h"
#include "../../../tools/ButtonBuilder.h"
#include "../../../tools/config_sdl.hpp"

#include "component_sdl_lib/asset_tools/text_sdl.h"
#include "component_sdl_lib/base/state_sdl.h"
#include "component_sdl_lib/panels/content_panel_sdl.h"
#include "component_sdl_lib/components/string_button_sdl.h"

namespace consoleart
{
class AsciiConvertStateSDL: public sdl::StateSDL, private AbstractAciiConversionState
{
private:
	int y;
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL pane;
public:
	AsciiConvertStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~AsciiConvertStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace consoleart */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
