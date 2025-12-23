//==============================================================================
// File       : ImageStateSDL.h
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_GUISDL_STATES_IMAGESTATESDL_H_
#define CONSOLEART_GUISDL_STATES_IMAGESTATESDL_H_

#include <functional>

#include "../../../abstract/AbstractState.h"

#include "consoleartlib/images/base/image.h"
#include "consoleartlib/images/interfaces/ianimated.hpp"
#include "consoleartlib/image_tools/image_tools.h"

#include "component_sdl_lib/base/state_sdl.h"

namespace consoleart
{
class ImageStateSDL : public sdl::StateSDL, private AbstractState
{
private:
	struct Frame
	{
		SDL_Texture* texture = nullptr;
		int delay = 0;
	};
	consoleartlib::Image* IMAGE;
	std::unique_ptr<unsigned char[]> imageRGBA;
	float scaleX;
	float scaleY;
	float scale;
	int newW;
	int newH;
	bool play;
	size_t currentFrameID;
	SDL_Rect imgSize;
	std::vector<Frame> frames;
	unsigned int detectSDLFormat();
	void swapPage(bool left);
	SDL_Texture* convertImageToTexture();
	void cleanFrames();
public:
	ImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager);
	virtual ~ImageStateSDL();
	virtual void handleTick(SDL_Event& event) override;
	virtual void onReturn() override;
	virtual void render() override;
	virtual void onWindowResize() override;
};

} /* namespace consoleart */

#endif /* CONSOLEART_GUISDL_STATES_IMAGESTATESDL_H_ */
