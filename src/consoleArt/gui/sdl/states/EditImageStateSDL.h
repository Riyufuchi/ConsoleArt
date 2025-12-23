//==============================================================================
// File       : EditImageState.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_EDITIMAGESTATE_H_
#define CONSOLEART_GUISDL_EDITIMAGESTATE_H_

#include <functional>

#include "../../../abstract/AbstractState.h"
#include "../../../tools/ButtonBuilder.h"

#include "component_sdl_lib/base/state_sdl.h"
#include "component_sdl_lib/panels/content_panel_sdl.h"
#include "component_sdl_lib/components/image_button_sdl.h"

namespace consoleart
{
class EditImageStateSDL : public sdl::StateSDL, private AbstractState
{
private:
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL pane;
public:
	EditImageStateSDL(sdl::WindowInfo& winInfo, ButtonBuilder& buttons, Controller& controller, StateManager& stateManager);
	virtual ~EditImageStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void render() override;
	virtual void onReturn() override;
	virtual void onWindowResize() override;
};
} /* namespace consoleart */
#endif /* CONSOLEART_GUISDL_EDITIMAGESTATE_H_ */
