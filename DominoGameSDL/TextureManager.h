#pragma once

#include <SDL.h>
#include <map>
#include <string>

class TextureManager {
public:
	bool loadTexture(const char* fileName, std::string id, SDL_Renderer* ren);

	void drawTexture(std::string id, int xpos, int ypos, int width, int height, SDL_Renderer* ren, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static void drawRectangle(SDL_Renderer* renderer, int xpos, int ypos,  int width, int height);

	static TextureManager* Instance();

private:
	std::map<std::string, SDL_Texture*> textureMap;
	TextureManager() {};
	static TextureManager* instance;
};
