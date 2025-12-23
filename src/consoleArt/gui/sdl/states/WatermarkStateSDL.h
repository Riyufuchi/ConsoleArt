//==============================================================================
// File       : WatermarkStateSDL.h
// Author     : riyufuchi
// Created on : Mar 08, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_WATERMARKSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_WATERMARKSTATESDL_H_

#include <vector>
#include <memory>

#include "../../../abstract/AbstractState.h"
#include "../../../tools/ButtonBuilder.h"
#include "../../../tools/config_sdl.hpp"
#include "consoleartlib/image_tools/image_tools.h"

#include "component_sdl_lib/base/state_sdl.h"
#include "component_sdl_lib/panels/content_panel_sdl.h"
#include "component_sdl_lib/components/label_sdl.h"
#include "component_sdl_lib/components/image_button_sdl.h"
#include "component_sdl_lib/components/string_button_sdl.h"
#include "component_sdl_lib/asset_tools/text_sdl.h"

namespace consoleart
{
class WatermarkStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	const int SIZE = 32;
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL* pane;
	sdl::ContentPanelSDL mainPane;
	sdl::ContentPanelSDL selectPane;
	sdl::LabelSDL* selectedWatermark;
	sdl::LabelSDL* imageNameLabel;
	consoleartlib::Image* watermark;
	std::atomic<bool> textUpdated;
	int y;
	void selectWatermarkEvent();
	void applytWatermarkEvent();
public:
	WatermarkStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~WatermarkStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace consoleart */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
