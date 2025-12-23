//==============================================================================
// File       : ImageFilterStateSDL.h
// Author     : riyufuchi
// Created on : May 24, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_IMAGEFILTERSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_IMAGEFILTERSTATESDL_H_

#include <future>

#include "../../../../console_art/abstract/AbstractState.h"
#include "../../../../console_art/tools/config_sdl.hpp"
#include "consoleartlib/image_tools/filter.h"
#include "../../../tools/general_tools.hpp"
// SDL
#include "component_sdl_lib/panels/content_panel_sdl.h"
#include "component_sdl_lib/components/string_button_sdl.h"
#include "component_sdl_lib/asset_tools/text_sdl.h"

namespace consoleart
{

class ImageFilterStateSDL : public sdl::StateSDL, private AbstractState
{
private:
	enum FilterType
	{
		MATRIX,
		PURPLEFIER
	};
	sdl::ContentPanelSDL pane;
public:
	ImageFilterStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager);
	virtual ~ImageFilterStateSDL() = default;
	bool applyFilter(const std::string& filter);
	void applyFilterEvent(std::string filter);
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};

} /* namespace consoleart */

#endif /* CONSOLEART_GUISDL_STATES_IMAGEFILTERSTATESDL_H_ */
