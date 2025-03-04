//==============================================================================
// File       : SelectImageStateSDL.h
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_ASCIICONVERTSTATESDL_H_
#define CONSOLEART_GUISDL_STATES_ASCIICONVERTSTATESDL_H_

#include <vector>
#include <memory>
#include <future>

#include "../../abstract/AbstractState.h"
#include "../../tools/ButtonBuilder.h"

#include "../../../sdl/assets/StringSDL.h"
#include "../../../sdl/abstract/StateSDL.h"
#include "../../../sdl/components/ContentPanelSDL.h"
#include "../../../sdl/components/StringButtonSDL.h"

namespace ConsoleArt
{
class AsciiConvertStateSDL: public sdl::StateSDL, private AbstractState
{
private:
	int y;
	ButtonBuilder& buttons;
	sdl::ContentPanelSDL* pane;
	std::vector<std::pair<ImageUtils::AsciiConverter::CHAR_SETS, std::string>> texts;
	void converImage(ImageUtils::AsciiConverter::CHAR_SETS charSet);
public:
	AsciiConvertStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons);
	virtual ~AsciiConvertStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onWindowResize() override;
	virtual void onReturn() override;
	virtual void render() override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUISDL_STATES_SELECTIMAGESTATESDL_H_ */
