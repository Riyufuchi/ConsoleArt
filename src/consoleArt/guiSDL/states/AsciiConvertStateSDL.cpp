//==============================================================================
// File       : SelectImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Mar 8, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiConvertStateSDL.h"

namespace ConsoleArt
{
AsciiConvertStateSDL::AsciiConvertStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractAciiConversionState(controller, stateManager), buttons(buttons)
{
	const std::string FONT = "assets/TF2Build.ttf";
	const int SIZE = 32;
	const SDL_Color color {255, 105, 180, 255};
	const SDL_Color colorHover {255, 179, 222, 255};
	//
	this->y = 0;
	this->pane = new sdl::ContentPanelSDL(0, 0);
	for (const auto& textPair : texts)
	{
		pane->addComponent(y, new sdl::StringButtonSDL(0, 0, new sdl::StringSDL(textPair.second, FONT, SIZE, color, renderer),
				colorHover, [&](){ converImageEvent(textPair.first); }));
		y++;
	}
	onWindowResize();
}

AsciiConvertStateSDL::~AsciiConvertStateSDL()
{
	delete pane;
}

void AsciiConvertStateSDL::handleTick(SDL_Event& event)
{
	pane->checkHoverOverContent(winInfo.mouseX, winInfo.mouseY);
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN: pane->tickOnClick(); break;
		case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) stateManager.switchState(WindowState::EDIT_IMAGE); break;
	}
}

void AsciiConvertStateSDL::onWindowResize()
{
	pane->center(winInfo.w, winInfo.h);
	pane->reposeContent();
}

void AsciiConvertStateSDL::onReturn()
{
	onWindowResize();
}

void AsciiConvertStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane->draw(renderer);
}

} /* namespace ConsoleArt */
