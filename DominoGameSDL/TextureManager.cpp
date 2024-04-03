#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

bool TextureManager::LoadTexture(const char* fileName, std::string id, SDL_Renderer* ren)
{
	SDL_Surface* tmpSurfce = IMG_Load(fileName);

    if(tmpSurfce == 0)
    {
		std::cout << "tmpSurface not created!" << std::endl;
		return false;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurfce);
	SDL_FreeSurface(tmpSurfce);

    if(tex != 0)
    {
        m_textureMap[id] = tex;
		return true;
	}
	
	return false;
}

void TextureManager::DrawTexture(std::string id, int xPos, int yPos, int width, int height, SDL_Renderer* ren, int angle, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
    destRect.x = xPos;
    destRect.y = yPos;

    SDL_RenderCopyEx(ren, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::DrawRectangle(SDL_Renderer* renderer, Vector2D rectPos, Vector2D rectSize)
{
    SDL_Rect fillRect = { rectPos.x, rectPos.y, rectSize.x, rectSize.y };
    SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
	SDL_RenderFillRect(renderer, &fillRect);
}

TextureManager* TextureManager::Instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new TextureManager();

        return m_instance;
	}

    return m_instance;
}

TextureManager* TextureManager::m_instance = 0;
