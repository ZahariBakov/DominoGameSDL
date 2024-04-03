#pragma once

#include <SDL.h>
#include <map>
#include <string>

#include "Tools/Vector2D.h"

class TextureManager
{
private:
    TextureManager() {};
    ~TextureManager() {};

public:
    auto LoadTexture(const char* fileName, std::string id, SDL_Renderer* ren) -> bool;

    void DrawTexture(std::string id, int xPos, int yPos, int width, int height, SDL_Renderer* ren, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    static void DrawRectangle(SDL_Renderer* renderer, Vector2D rectPos,  Vector2D rectSize);

    static auto Instance() -> TextureManager*;

private:
    std::map<std::string, SDL_Texture*> m_textureMap;
    static TextureManager* m_instance;
};
