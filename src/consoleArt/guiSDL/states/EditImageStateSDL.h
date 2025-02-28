//==============================================================================
// File       : EditImageState.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Feb 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_EDITIMAGESTATE_H_
#define CONSOLEART_GUISDL_EDITIMAGESTATE_H_

#include <functional>

#include "../../../sdl/abstract/StateSDL.h"
#include "../../../sdl/assets/StringSDL.h"
#include "../../../sdl/components/ContentPanelSDL.h"
#include "../../../sdl/components/ImageButtonSDL.h"
#include "../../tools/ButtonBuilder.h"

namespace ConsoleArt
{
class EditImageStateSDL: public sdl::StateSDL
{
private:
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL* pane;
public:
	EditImageStateSDL(SDL_Renderer* renderer, sdl::WindowInfo& winInfo, ButtonBuilder& buttons, std::function<void()> baclBtnEvt);
	virtual ~EditImageStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void render() override;
	virtual void onReturn() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_EDITIMAGESTATE_H_ */
