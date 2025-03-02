//==============================================================================
// File       : ImageStateSDL.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Mar 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_IMAGESTATESDL_H_
#define CONSOLEART_GUISDL_STATES_IMAGESTATESDL_H_

#include <SDL2/SDL_image.h>
#include <functional>

#include "../../../images/Image.h"
#include "../../../sdl/abstract/StateSDL.h"
#include "../../controller/Controller.h"
#include "../StateManager.h"

namespace ConsoleArt
{
class ImageStateSDL : public sdl::StateSDL
{
private:
	Controller& controller;
	StateManager& stateManager;
	const Images::Image* IMAGE;
	SDL_Texture* texture;
	float scaleX;
	float scaleY;
	float scale;
	int newW;
	int newH;
	SDL_Rect imgSize;
public:
	ImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager);
	virtual ~ImageStateSDL();
	virtual void handleTick(SDL_Event &event) override;
	virtual void onReturn() override;
	virtual void render() override;
	virtual void onWindowResize() override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUISDL_STATES_IMAGESTATESDL_H_ */
