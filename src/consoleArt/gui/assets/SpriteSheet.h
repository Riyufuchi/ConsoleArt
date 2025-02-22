#ifndef CONSOLEART_GUI_ASSETS_SPRITE_SHEET_H_
#define CONSOLEART_GUI_ASSETS_SPRITE_SHEET_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>

namespace ConsoleArt
{
class SpriteSheet
{
private:
	SDL_Surface* spriteSheet;
	SDL_Renderer* renderer;
	SDL_Texture* textureSheet;
	SDL_Surface* sourceSurface;
	std::unordered_map<std::string, SDL_Texture*> textureCache;
	SDL_Texture* getCroppedTexture(int x, int y, int width, int height);
public:
	SpriteSheet(const char* path, SDL_Renderer* renderer);
	~SpriteSheet();
	SDL_Texture* getTexture(const std::string& textureName);
	void prepareTexture(const std::string textureName, int x, int y, int width, int height);
};
}
#endif
