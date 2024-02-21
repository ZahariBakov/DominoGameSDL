#pragma once

#include "Game.h"

#include <map>

class TextureManager {
public:
	bool loadTexture(const char* fileName, std::string id, SDL_Renderer* ren);

	void drawTexture(std::string id, int xpos, int ypos, int width, int height, int angle, SDL_Renderer* ren, SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL);
	static void drawRectangle(SDL_Renderer* renderer, int xpos, int ypos,  int width, int height);

	static TextureManager* Instance();

private:
	std::map<std::string, SDL_Texture*> textureMap;
	TextureManager() {};
	static TextureManager* instance;
};
