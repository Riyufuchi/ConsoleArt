//==============================================================================
// File       : SelectImageStateSDL.h
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_
#define CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_

#include <vector>
#include <memory>

#include "../../abstract/AbstractState.h"
#include "../../tools/ButtonBuilder.h"

#include "../../../sdl/abstract/StateSDL.h"
#include "../../../sdl/components/ContentPanelSDL.h"
#include "../../../sdl/assets/StringSDL.h"

namespace ConsoleArt
{
class SelectImageStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	int y;
	ButtonBuilder& buttons;
	std::vector<std::unique_ptr<sdl::StringSDL>> imageNames;
public:
	SelectImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~SelectImageStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
