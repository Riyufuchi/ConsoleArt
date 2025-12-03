//==============================================================================
// File       : ImageStateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 28, 2025
// Last edit  : Nov 18, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "ImageStateSDL.h"

namespace consoleart
{
ImageStateSDL::ImageStateSDL(sdl::WindowInfo& winInfo, Controller& controller, StateManager& stateManager) : sdl::StateSDL(winInfo), AbstractState(controller, stateManager), IMAGE(nullptr)
{
	this->imageRGBA = nullptr;
	this->scaleX = 0;
	this->scaleY = 0;
	this->newW = 0;
	this->newH = 0;
	this->play = true;
	this->currentFrameID = 0;
	this->scale = 0;
}

ImageStateSDL::~ImageStateSDL()
{
	cleanFrames();
}

void ImageStateSDL::handleTick(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_ESCAPE: stateManager.switchState(WindowState::MAIN); break;
			case SDLK_LEFT: swapPage(true); break;
			case SDLK_RIGHT: swapPage(false); break;
			case SDLK_SPACE: play = !play; break;
		}
	}
}

void ImageStateSDL::swapPage(bool left)
{
	if (IMAGE->getImageInfo().multipage)
	{
		if (left)
		{
			if (currentFrameID > 0)
				--currentFrameID;
		}
		else
		{
			if (currentFrameID + 1 < frames.size())
				++currentFrameID;
		}
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
				case consoleartlib::RGBA: return SDL_PIXELFORMAT_RGB24;
				case consoleartlib::BGRA: return SDL_PIXELFORMAT_BGR24;
				default: return SDL_PIXELFORMAT_UNKNOWN;
			}
		case 4:
			switch (IMAGE->getPixelFormat())
			{
				case consoleartlib::RGBA: return SDL_PIXELFORMAT_RGBA32;
				case consoleartlib::BGRA: return SDL_PIXELFORMAT_BGRA32;
				default: return SDL_PIXELFORMAT_UNKNOWN;
			}
		default: return SDL_PIXELFORMAT_UNKNOWN;
	}
}

void ImageStateSDL::onReturn()
{
	this->IMAGE = controller.getSelectedImage();
	if (!IMAGE)
		return;
	cleanFrames();
	currentFrameID = 0;
	if (IMAGE->getImageInfo().multipage)
	{
		consoleartlib::IMultiPage* imp = dynamic_cast<consoleartlib::IMultiPage*>(IMAGE);
		for (size_t i = 0; i < imp->getPageCount(); i++)
			{
				Frame f;
				imp->selectPage(i);
				f.texture = convertImageToTexture();
				frames.emplace_back(f);
		}
	}
	else
		frames.emplace_back(Frame{convertImageToTexture()});

	if (IMAGE->getImageInfo().animated)
	{
		auto gif = dynamic_cast<consoleartlib::IAnimated*>(IMAGE);
		for (size_t i = 0; i < frames.size(); i++)
		{
			frames[i].delay = gif->getFrameDelay(i);
		}
	}
	onWindowResize();
}

void ImageStateSDL::render()
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

	static Uint32 last = SDL_GetTicks();

	if (IMAGE->getImageInfo().animated && play)
	{
		Uint32 now = SDL_GetTicks();
		Frame& f = frames[currentFrameID];

		if (now - last >= (Uint32)f.delay)
		{
			currentFrameID++;
			if (currentFrameID >= frames.size())
				currentFrameID = 0;
			last = now;
		}
	}
	SDL_RenderCopy(renderer, frames[currentFrameID].texture, NULL, &imgSize);
}

SDL_Texture* ImageStateSDL::convertImageToTexture()
{
	consoleartlib::ImageInfo info = IMAGE->getImageInfo();

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); // Linear filtering (smoother scaling)

	// Determine the correct pixel format and masks
	Uint32 rmask, gmask, bmask, amask;
	switch (IMAGE->getPixelFormat())
	{
		case consoleartlib::RGBA:
			rmask = 0x000000FF;
			gmask = 0x0000FF00;
			bmask = 0x00FF0000;
			amask = 0xFF000000;
		break;
		case consoleartlib::BGRA:
			rmask = 0x00FF0000;
			gmask = 0x0000FF00;
			bmask = 0x000000FF;
			amask = 0xFF000000;
		break;
		default:
			SDL_Log("Unknown pixel format");
		return 0;
	}

	if (info.bits < 24)
		info.bits = 24;

	// This program treats pallted PCX as standard 24-bit PCX
	switch (IMAGE->getImageInfo().imageFormat)
	{
		case consoleartlib::ImageType::DCX: imageRGBA = ImageUtils::ImageTools::convertPlanarPCXToInterleaved(((consoleartlib::ImageDCX&)*IMAGE).getSelectedPage()); break;
		case consoleartlib::ImageType::PCX: imageRGBA = ImageUtils::ImageTools::convertPlanarPCXToInterleaved((consoleartlib::ImagePCX&)*IMAGE); break;
		default: imageRGBA = IMAGE->getImageData(); break;
	}

	if (!imageRGBA.get())
	{
		SDL_Log("imageRGBA is nullptr!");
		return 0;
	}

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
		(void*)imageRGBA.get(), info.width, info.height, info.bits, info.width * (info.bits / 8),
		rmask, gmask, bmask, amask);

	// Attach SDL's memory management to avoid leaks
	if (!surface)
	{
		SDL_Log("Failed to create surface: %s", SDL_GetError());
		return 0;
	}

	// Convert surface to texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void ImageStateSDL::cleanFrames()
{
	if (!frames.empty())
	{
		for (size_t i = 0; i < frames.size(); i++)
		{
			if (frames[i].texture)
				SDL_DestroyTexture(frames[i].texture);
		}
		frames.clear();
	}
}

void ImageStateSDL::onWindowResize()
{
	if (!IMAGE)
		return;
	// Calculate scaling factor (preserve aspect ratio)
	scaleX = static_cast<float>(winInfo.w) / IMAGE->getWidth();
	scaleY = static_cast<float>(winInfo.h) / IMAGE->getHeight();
	scale = std::max(0.01f, std::min(scaleX, scaleY)); // Ensure scale is never zero
	// Calculate new width and height
	newW = static_cast<int>(IMAGE->getWidth() * scale);
	newH = static_cast<int>(IMAGE->getHeight() * scale);
	imgSize.w = std::max(1, std::min(winInfo.w, newW));
	imgSize.h = std::max(1, std::min(winInfo.h, newH));
	imgSize.x = std::max(0, (winInfo.w - newW) / 2);
	imgSize.y = std::max(0, (winInfo.h - newH) / 2);
}

} /* namespace consoleart */
