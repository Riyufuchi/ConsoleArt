//==============================================================================
// File       : ImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Mar 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageStateSDL.h"

namespace ConsoleArt
{
ImageStateSDL::ImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager) : sdl::StateSDL(winInfo), controller(controller), stateManager(stateManager), IMAGE(nullptr)
{
	this->texture = nullptr;
	this->imageRGBA = nullptr;
	this->scaleX = 0;
	this->scaleY = 0;
	this->newW = 0;
	this->newH = 0;
	this->scale = 0;
}

ImageStateSDL::~ImageStateSDL()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void ImageStateSDL::handleTick(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		stateManager.switchState(WindowState::EDIT_IMAGE);
	}
}

void ImageStateSDL::onReturn()
{
	this->IMAGE = controller.getSelectedImage();
	Images::ImageInfo info = IMAGE->getImageInfo();

	if (info.bits < 24)
		info.bits = 24;
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*) IMAGE->getImageData(),
		info.width, info.height, info.bits, info.width * (info.bits / 8),
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	if (!surface)
	{
		SDL_Log("Failed to create surface: %s", SDL_GetError());
		return;
	}

	// Convert to texture
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); // Free the surface after texture creation

	if (!texture) {
		SDL_Log("Failed to create texture: %s", SDL_GetError());
		return;
	}
	onWindowResize();
}

void ImageStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	// Render the image with the new size
	SDL_RenderCopy(renderer, texture, NULL, &imgSize);
}

void ImageStateSDL::onWindowResize()
{
	if (!IMAGE)
		return;
	// Calculate scaling factor (preserve aspect ratio)
	scaleX = static_cast<float>(winInfo.w) / IMAGE->getWidth();
	scaleY = static_cast<float>(winInfo.h) / IMAGE->getHeight();
	scale = std::min(scaleX, scaleY); // Use the smaller scale to fit within bounds
	// Calculate new width and height
	newW = static_cast<int>(IMAGE->getWidth() * scale);
	newH = static_cast<int>(IMAGE->getHeight() * scale);
	imgSize.w = newW;
	imgSize.h = newH;
	imgSize.x = (winInfo.w - newW) / 2; // Center horizontally
	imgSize.y = (winInfo.h - newH) / 2; // Center vertically
}

} /* namespace ConsoleArt */
