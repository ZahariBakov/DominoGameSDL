#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "TextureManager.h"
#include "Domino.h"

class Game {
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();

	void render();
	void update();
	void handleEvents();
	void clean();
	void isClicked(int xDown, int yDown, int xUp, int yUp);

	bool isRunning() const;
	
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;

	int mouseDownX, mouseDownY, gameFlag;

	Domino dominoTiles;

	SDL_Texture* newTex,
		* menuTex,
		* menuTitleTex,
		* passTex,
		* classicTex;

	SDL_Rect newRect,
		menuRect,
		menuTitleRect,
		passRect,
		classicRect;
};
