//==============================================================================
// File       : SpriteSheetSDL.h
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Feb 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description:
//==============================================================================

#ifndef CONSOLEART_GUI_ASSETS_SPRITE_SHEET_H_
#define CONSOLEART_GUI_ASSETS_SPRITE_SHEET_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <utility>

namespace ConsoleArt
{
class SpriteSheetSDL
{
private:
	SDL_Surface* spriteSheet;
	SDL_Renderer* renderer;
	SDL_Texture* textureSheet;
	SDL_Surface* sourceSurface;
	std::unordered_map<std::string, SDL_Texture*> textureCache;
	SDL_Texture* getCroppedTexture(int x, int y, int width, int height);
public:
	SpriteSheetSDL(const char* path, SDL_Renderer* renderer);
	~SpriteSheetSDL();
	SDL_Texture* getTexture(const std::string& textureName);
	std::pair<SDL_Texture*, SDL_Texture*> getTexturePair(std::pair<std::string, std::string> IDs);
	void prepareTexture(const std::string textureName, int x, int y, int width, int height);
	void prepareTexturePair(std::pair<std::string, std::string> IDs, int x, int y, std::pair<int, int> size);
};
}
#endif
