//==============================================================================
// File       : ImageFilterStateSDL.h
// Author     : riyufuchi
// Created on : May 24, 2025
// Last edit  : May 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_IMAGEFILTERSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_IMAGEFILTERSTATESDL_H_

#include <future>

#include "../../abstract/AbstractState.h"
#include "../../tools/ConfigSDL.hpp"
#include "../../imageTools/Filter.h"
#include "../../tools/GeneralTools.hpp"
// SDL
#include "../../../sdl/panels/ContentPanelSDL.h"
#include "../../../sdl/components/StringButtonSDL.h"

namespace ConsoleArt
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

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUISDL_STATES_IMAGEFILTERSTATESDL_H_ */
