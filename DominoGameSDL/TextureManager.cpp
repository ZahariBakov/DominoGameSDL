#include "TextureManager.h"

bool TextureManager::loadTexture(const char* fileName, std::string id, SDL_Renderer* ren) {
	SDL_Surface* tmpSurfce = IMG_Load(fileName);

	if (tmpSurfce == 0) {
		std::cout << "tmpSurface not created!" << std::endl;
		return false;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurfce);
	SDL_FreeSurface(tmpSurfce);

	if (tex != 0) {
		textureMap[id] = tex;
		return true;
	}
	
	return false;
}

void TextureManager::drawTexture(std::string id, int xpos, int ypos, int width, int height, SDL_Renderer* ren, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = xpos;
	destRect.y = ypos;

	SDL_RenderCopyEx(ren, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawRectangle(SDL_Renderer* renderer, int xpos, int ypos, int width, int height) {
	SDL_Rect fillRect = { xpos, ypos, width, height };
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderFillRect(renderer, &fillRect);
}

TextureManager* TextureManager::Instance() {
	if (instance == 0) {
		instance = new TextureManager();

		return instance;
	}
	
	return instance;
}

TextureManager* TextureManager::instance = 0;
