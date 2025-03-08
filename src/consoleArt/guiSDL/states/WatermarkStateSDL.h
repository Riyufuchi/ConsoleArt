//==============================================================================
// File       : WatermarkStateSDL.h
// Author     : riyufuchi
// Created on : Mar 8, 2025
// Last edit  : Mar 8, 2025
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
#include "../../../sdl/components/ContentPanelSDL.h"
#include "../../../sdl/components/LabelSDL.h"
#include "../../../sdl/components/ImageButtonSDL.h"
#include "../../../sdl/components/StringButtonSDL.h"

namespace ConsoleArt
{
class WatermarkStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL* pane;
	sdl::LabelSDL* selectedWatermark;
	Images::Image* watermark;
	std::atomic<bool> textUpdated;
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
