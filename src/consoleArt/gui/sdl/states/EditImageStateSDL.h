//==============================================================================
// File       : EditImageState.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Nov 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_EDITIMAGESTATE_H_
#define CONSOLEART_GUISDL_EDITIMAGESTATE_H_

#include <functional>

#include "../../../abstract/AbstractState.h"
#include "../../../tools/ButtonBuilder.h"
#include "../../../imageTools/Filter.h"

#include "StateSDL.h"
#include "StringSDL.h"
#include "ContentPanelSDL.h"
#include "ImageButtonSDL.h"

namespace ConsoleArt
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
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_EDITIMAGESTATE_H_ */
