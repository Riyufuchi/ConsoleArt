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

unsigned int ImageStateSDL::detectSDLFormat()
{
	switch (IMAGE->getBits() / 8)
	{
		case 1: return SDL_PIXELFORMAT_INDEX8;  // Grayscale (1 channel)
		case 3:
			switch (IMAGE->getPixelFormat())
			{
				case Images::RGBA: return SDL_PIXELFORMAT_RGB24;
				case Images::BGRA: return SDL_PIXELFORMAT_BGR24;
				default: return SDL_PIXELFORMAT_UNKNOWN;
			}
		case 4:
			switch (IMAGE->getPixelFormat())
			{
				case Images::RGBA: return SDL_PIXELFORMAT_RGBA32;
				case Images::BGRA: return SDL_PIXELFORMAT_BGRA32;
				default: return SDL_PIXELFORMAT_UNKNOWN;
			}
		default: return SDL_PIXELFORMAT_UNKNOWN;
	}
}

void ImageStateSDL::onReturn()
{
	this->IMAGE = controller.getSelectedImage();
	Images::ImageInfo info = IMAGE->getImageInfo();

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");  // Linear filtering (smoother scaling)


	if (info.bits < 24)
		info.bits = 24;
	// Determine the correct pixel format and masks
	Uint32 rmask, gmask, bmask, amask;
	switch (IMAGE->getPixelFormat())
	{
		case Images::RGBA:
			rmask = 0x000000FF;
			gmask = 0x0000FF00;
			bmask = 0x00FF0000;
			amask = 0xFF000000;
		break;
		case Images::BGRA:
			rmask = 0x00FF0000;
			gmask = 0x0000FF00;
			bmask = 0x000000FF;
			amask = 0xFF000000;
		break;
		default:
			SDL_Log("Unknown pixel format");
		return;
	}

	if (info.planar)
		imageRGBA = ImageUtils::ImageTools::convertPlanarPCXToInterleaved((Images::ImagePCX&)*IMAGE);
	else
		imageRGBA = IMAGE->getImageData();

	// Create the surface with the correct color masks
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)imageRGBA,
			info.width, info.height, info.bits, info.width * (info.bits / 8),
			rmask, gmask, bmask, amask);

	if (!surface)
	{
		SDL_Log("Failed to create surface: %s", SDL_GetError());
		return;
	}

	// Convert surface to texture
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	//SDL_GetWindowSize(winInfo.window, &winInfo.w, &winInfo.h);
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
	//SDL_QueryTexture(texture, NULL, NULL, &imgSize.w, &imgSize.h);
	// Calculate scaling factor (preserve aspect ratio)
	scaleX = static_cast<float>(winInfo.w) / IMAGE->getWidth();
	scaleY = static_cast<float>(winInfo.h) / IMAGE->getHeight();
	scale = std::max(0.01f, std::min(scaleX, scaleY)); // Ensure scale is never zero
	SDL_Log("Scale: %f", scale);
	// Calculate new width and height
	newW = static_cast<int>(IMAGE->getWidth() * scale);
	newH = static_cast<int>(IMAGE->getHeight() * scale);
	SDL_Log("Window %d x %d", winInfo.w, winInfo.h);
	SDL_Log("Image %d x %d", newW, newH);
	imgSize.w = std::max(1, std::min(winInfo.w, newW));
	imgSize.h = std::max(1, std::min(winInfo.h, newH));
	imgSize.x = std::max(0, (winInfo.w - newW) / 2);
	imgSize.y = std::max(0, (winInfo.h - newH) / 2);
}

} /* namespace ConsoleArt */
