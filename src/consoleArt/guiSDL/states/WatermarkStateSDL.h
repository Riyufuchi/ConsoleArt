//==============================================================================
// File       : WatermarkStateSDL.h
// Author     : riyufuchi
// Created on : Mar 8, 2025
// Last edit  : Apr 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_WATERMARKSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_WATERMARKSTATESDL_H_

#include <vector>
#include <memory>

#include "../../abstract/AbstractState.h"
#include "../../tools/ButtonBuilder.h"
#include "../../imageTools/ImageTools.h"

#include "../../../sdl/assets/StringSDL.h"
#include "../../../sdl/abstract/StateSDL.h"
#include "../../../sdl/panels/ContentPanelSDL.h"
#include "../../../sdl/components/LabelSDL.h"
#include "../../../sdl/components/ImageButtonSDL.h"
#include "../../../sdl/components/StringButtonSDL.h"

namespace ConsoleArt
{
class WatermarkStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	const std::string FONT = "assets/TF2secondary.ttf";
	const int SIZE = 32;
	const SDL_Color COLOR {255, 105, 180, 255};
	const SDL_Color COLOR_HOVER {255, 179, 222, 255};
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL* pane;
	sdl::ContentPanelSDL* mainPane;
	sdl::ContentPanelSDL* selectPane;
	sdl::LabelSDL* selectedWatermark;
	Images::Image* watermark;
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
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
