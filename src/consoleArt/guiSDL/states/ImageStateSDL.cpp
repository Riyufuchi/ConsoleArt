//==============================================================================
// File       : ImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Feb 28, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "ImageStateSDL.h"

namespace ConsoleArt
{
ImageStateSDL::ImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller) : sdl::StateSDL(winInfo), controller(controller), IMAGE(nullptr)
{
	this->texture = nullptr;
	this->scaleX = 0;
	this->scaleY = 0;
	this->newW = 0;
	this->newH = 0;
	this->scale = 0;
}

ImageStateSDL::~ImageStateSDL()
{
}

void ImageStateSDL::handleTick(SDL_Event &event)
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

void ImageStateSDL::onReturn()
{
	this->IMAGE = controller.getSelectedImage();
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
			(void*) IMAGE->getImageData(), IMAGE->getWidth(),
			IMAGE->getHeight(), IMAGE->getBits(), IMAGE->getWidth() * (IMAGE->getBits()/8), // Assuming 4 bytes per pixel (RGBA)
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 // RGBA masks
			);

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

	SDL_GetRendererOutputSize(renderer, &winInfo.w, &winInfo.h);

	// Get original image size
	int imgW = IMAGE->getWidth();
	int imgH = IMAGE->getHeight();

	// Calculate scaling factor (preserve aspect ratio)
	scaleX = static_cast<float>(winInfo.w) / imgW;
	scaleY = static_cast<float>(winInfo.h) / imgH;
	scale = std::min(scaleX, scaleY); // Use the smaller scale to fit within bounds

	// Calculate new width and height
	newW = static_cast<int>(imgW * scale);
	newH = static_cast<int>(imgH * scale);

	// Center the image

	imgSize.w = newW;
	imgSize.h = newH;
	imgSize.x = (winInfo.w - newW) / 2; // Center horizontally
	imgSize.y = (winInfo.h - newH) / 2; // Center vertically
}

void ImageStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	// Render the image with the new size
	SDL_RenderCopy(renderer, texture, NULL, &imgSize);
}

} /* namespace ConsoleArt */
