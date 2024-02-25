#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "TextureManager.h"
#include "Domino.h"
#include "Player.h"
#include "Table.h"
#include "SoundManager.h"

class Game {
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();

	void LoadAndPlaySound();

	void render();
	void handleEvents();
	void clean();
	void isClicked(int xDown, int yDown, int xUp, int yUp);
	bool isSeleckted(int idx) const;

	bool isRunning() const;
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running, isInMatrix, toPlaySound;
	//bool playerTileClicked(int idx) const;
	int mouseDownX, mouseDownY, gameFlag, playerFlag, difficulty, playedTileToWin, tilesType;

	SDL_Texture* newTex,
		* menuTex,
		* menuTitleTex,
		* passTex,
		* classicTex,
		* playerTex,
		* firstPlayerNumTex,
		* secondPlayerNumTex,
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
		firstPlayerNumRect,
		secondPlayerNumRect,
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
	void playSound(std::string id);
};
