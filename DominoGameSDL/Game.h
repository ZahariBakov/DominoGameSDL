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

enum class GameFlag {
	Welcome,
	MainMenu,
	Playing,
	Ok,
	Win
};

enum PlayerFlag { First, Second };
enum Difficulty { Easy, Normal, Hard, All, None };
enum class DominoType { Classic, Vehicle, Flowers, Butterflies, None };

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
	bool isSelected(int idx) const;

	bool isRunning() const;
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running, isInMatrix, toPlaySound, isReset;
	int mouseDownX, mouseDownY, gameFlag, playedTileToWin, tilesType, tileIdx, playerWin;

	SDL_Texture* newTex,
		* menuTex,
		* menuTitleTex,
		* passTex,
		* classicTex,
		* vehicleTex,
		* flowersTex,
		* butterfliesTex,
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
		* blackTex,
		* quitTex,
		* winTex,
		* zeroTex,
		* oneTex,
		* twoTex,
		* threeTex,
		* fourTex,
		* fiveTex,
		* sixTex,
		* sevenTex,
		* eightTex,
		* nineTex,
		* resetTex,
		* isResetTex;

	SDL_Rect newRect,
		menuRect,
		menuTitleRect,
		passRect,
		classicRect,
		vehicleRect,
		flowersRect,
		butterfliesRect,
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
		blackRect,
		quitRect,
		winRect,
		zeroRect,
		oneRect,
		twoRect,
		threeRect,
		fourRect,
		fiveRect,
		sixRect,
		seventRect,
		eightRect,
		nineRect,
		resetRect,
		isResetRect;

	void startNewGame();
	void nextPlayer();
	void playSound(std::string id);
	bool checkForWin() const;
	void rotate(int idx);
};
