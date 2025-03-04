//==============================================================================
// File       : SelectImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Mar 3, 2025
// Last edit  : Mar 3, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "AsciiConvertStateSDL.h"

namespace ConsoleArt
{
AsciiConvertStateSDL::AsciiConvertStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager, ButtonBuilder& buttons) : StateSDL(winInfo), AbstractState(controller, stateManager), buttons(buttons)
{
	const std::string FONT = "TF2Build.ttf";
	const int SIZE = 32;
	const SDL_Color color {255, 105, 180, 255};
	const SDL_Color colorHover {255, 179, 222, 255};
	//
	this->y = 0;
	this->pane = new sdl::ContentPanelSDL(0, 0);
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::BASIC, "BASIC"});
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::BASIC_INVERTED, "BASIC INVERTED"});
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::PRECISE, "PRECISE"});
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::PRECISE_INVERTED, "PRECISE INVERTED"});
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::DETAILED, "DETAILED"});
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::DETAILED_INVERTED, "DETAILED INVERTED"});
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::SHADES, "SHADES"});
	texts.push_back({ImageUtils::AsciiConverter::CHAR_SETS::SHADES_INVERTED, "SHADES INVERTED"});
	for (const auto& textPair : texts)
	{
		pane->addComponent(y, new sdl::StringButtonSDL(0, 0, new sdl::StringSDL(textPair.second, FONT, SIZE, color, renderer),
				new sdl::StringSDL(textPair.second, FONT, SIZE, colorHover, renderer), [&](){ converImage(textPair.first); }));
		y++;
	}
	onWindowResize();
}

AsciiConvertStateSDL::~AsciiConvertStateSDL()
{
	delete pane;
}

void AsciiConvertStateSDL::converImage(ImageUtils::AsciiConverter::CHAR_SETS charSet)
{
	std::thread([asciiChar = charSet, this](){ controller.convertImage(controller.getSelectedImage(), asciiChar); }).detach();
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
}

void AsciiConvertStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	pane->draw(renderer);
}

} /* namespace ConsoleArt */
