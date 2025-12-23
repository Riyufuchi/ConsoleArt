//==============================================================================
// File       : MainStateSDL.h
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_MAINSTATE_H_
#define CONSOLEART_GUISDL_MAINSTATE_H_

#include <atomic>
#include <thread>
#include <string>

#include "../../../../console_art/tools/button_builder.h"
#include "../../../../console_art/tools/config_sdl.hpp"
#include "../../../abstract/abstract_state.h"
#include "component_sdl_lib/base/state_sdl.h"
#include "component_sdl_lib/asset_tools/sprite_sheet_sdl.h"
#include "component_sdl_lib/panels/content_panel_sdl.h"
#include "component_sdl_lib/components/image_button_sdl.h"
#include "component_sdl_lib/components/label_sdl.h"


namespace consoleart
{
class MainStateSDL : public sdl::StateSDL, private AbstractState
{
private:
	ButtonBuilder& buttons;
	sdl::LabelSDL* selectedImageString;
	sdl::ContentPanelSDL pane;
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
} /* namespace consoleart */
#endif /* CONSOLEART_GUISDL_MAINSTATE_H_ */
