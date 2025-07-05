//==============================================================================
// File       : SelectImageStateSDL.h
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Jul 05, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_
#define CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_

#include <vector>
#include <memory>

#include "../../abstract/AbstractState.h"
#include "../../tools/ButtonBuilder.h"
#include "../../tools/ConfigSDL.hpp"

#include "StateSDL.h"
#include "ContentPanelSDL.h"
#include "StringButtonSDL.h"
#include "StringSDL.h"

namespace ConsoleArt
{
class SelectImageStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	int y;
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL pane;
	std::vector<std::unique_ptr<sdl::StringSDL>> imageNames;
public:
	SelectImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~SelectImageStateSDL();
	void createUI();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
