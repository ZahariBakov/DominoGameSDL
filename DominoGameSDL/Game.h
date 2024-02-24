#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "TextureManager.h"
#include "Domino.h"
#include "Player.h"
#include "Table.h"

class Game {
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	void render();
	void handleEvents();
	void clean();
	void isClicked(int xDown, int yDown, int xUp, int yUp);
	bool isSeleckted(int idx) const;

	bool isRunning() const;
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running, isInMatrix;
	//bool playerTileClicked(int idx) const;
	int mouseDownX, mouseDownY, gameFlag, playerFlag, difficulty, playedTileToWin, tilesType;

	SDL_Texture* newTex,
		* menuTex,
		* menuTitleTex,
		* passTex,
		* classicTex,
		* playerTex,
		* playerNumTex,
		* okTex,
		* firstPlayerWinTex,
		* secondPlayerWinTex,
		* easyTex,
		* normalTex,
		* hardTex,
		* whiteTex,
		* blackTex;

	SDL_Rect newRect,
		menuRect,
		menuTitleRect,
		passRect,
		classicRect,
		playerRect,
		playerNumRect,
		okRect,
		firstPlayerWinRect,
		secondPlayerWinRect,
		easyRect,
		normalRect,
		hardRect,
		whiteRect,
		blackRect;

	void startNewGame();
	int nextPlayer(int currPlayer);
	void CoordinatesToInt();
};
