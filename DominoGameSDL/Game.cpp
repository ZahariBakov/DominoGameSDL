#include "Game.h"

#include <iostream>

Game::Game() {
	Game::window =   NULL;
	Game::renderer = NULL;

	Game::running = true;

	Game::mouseDownX = 0;
	Game::mouseDownY = 0;
	Game::gameFlag = 0;

	Game::newTex =       NULL;
	Game::menuTex =      NULL;
	Game::menuTitleTex = NULL;
	Game::passTex =      NULL;
	Game::classicTex =   NULL;

	Game::newRect =       { 0, 0, 0, 0 };
	Game::menuRect =      { 0, 0, 0, 0 };
	Game::menuTitleRect = { 0, 0, 0, 0 };
	Game::passRect =      { 0, 0, 0, 0 };
	Game::classicRect =   { 0, 0, 0, 0 };
}

Game::~Game() {
	delete window;
	delete renderer;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success!\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) {
			std::cout << "Window creation success!\n";
			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0) {
				std::cout << "Renderer creation success!\n";
				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);

				TextureManager::Instance()->loadTexture("assets/welcome.jpg", "welcome", renderer);

			}
			else {
				std::cout << "Renderer init failed!\n";
				return false;
			}
		}
		else {
			std::cout << "Window init failed!\n";
			return false;
		}
	}
	else {
		std::cout << "SDL init fail!\n";
		return false;
	}
	std::cout << "Init success!\n";
	running = true;

	return true;
}

bool Game::ttf_init() {
	if (TTF_Init() == -1) {
		return false;
	}

	TTF_Font* font1 = TTF_OpenFont("fonts/Arcade.ttf", 36);
	TTF_Font* font2 = TTF_OpenFont("fonts/Arcade.ttf", 90);

	if (font1 == NULL || font2 == NULL) {
		std::cout << "Font 1 or Font 2" << std::endl;
		return false;
	}

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh); // get window size

	SDL_Surface* tempSurfaceText = NULL;

	tempSurfaceText = TTF_RenderText_Blended(font1, "NEW GAME", { 255, 255, 255, 255 });
	newTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "MENU", { 255, 255, 255, 255 });
	menuTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "MENU", { 255, 255, 255, 255 });
	menuTitleTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "PASS", { 255, 255, 255, 255 });
	passTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "CLASSIC", { 255, 255, 255, 255 });
	classicTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	int tw, th;
	SDL_QueryTexture(newTex, 0, 0, &tw, &th);
	newRect = { 10, 10, tw, th };

	SDL_QueryTexture(menuTex, 0, 0, &tw, &th);
	menuRect = { 10, 40, tw, th };

	SDL_QueryTexture(menuTitleTex, 0, 0, &tw, &th);
	menuTitleRect = { ww / 2 - tw / 2, 40, tw, th };

	SDL_QueryTexture(passTex, 0, 0, &tw, &th);
	passRect = { 10, 70, tw, th };

	SDL_QueryTexture(classicTex, 0, 0, &tw, &th);
	classicRect = { 10, 150, tw, th };

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font1);
	TTF_CloseFont(font2);

	return true;
}

void Game::render() {
	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	SDL_RenderClear(renderer);

	if (Game::gameFlag == 0) {
		TextureManager::Instance()->drawTexture("welcome", 0, 0, ww, wh, renderer, SDL_FLIP_NONE);
		SDL_RenderCopy(renderer, newTex, NULL, &newRect);
	}
	else if (Game::gameFlag == 1) {
		SDL_RenderCopy(renderer, menuTitleTex, NULL, &menuTitleRect);
		SDL_RenderCopy(renderer, classicTex, NULL, &classicRect);
	}
	else {
		SDL_RenderCopy(renderer, menuTex, NULL, &menuRect);
		SDL_RenderCopy(renderer, passTex, NULL, &passRect);
	}	

	SDL_RenderPresent(renderer);
}

void Game::update() {}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		int msx, msy;

		switch (event.type) {
			case SDL_QUIT: running = false; break;
			case SDL_MOUSEBUTTONDOWN: {
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_GetMouseState(&msx, &msy);
					Game::mouseDownX = msx;
					Game::mouseDownY = msy;
				}
			}; break;
			case SDL_MOUSEBUTTONUP: {
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_GetMouseState(&msx, &msy);
					Game::isClicked(mouseDownX, mouseDownY, msx, msy);
				}
			}; break;

			default: break;
			}
	}
}

void Game::clean() {
	std::cout << "Cleaning game!\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::isClicked(int xDown, int yDown, int xUp, int yUp) {
	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	int btnX = 10;
	int btnY = 14;
	int btnW = 150;
	int btnH = 23;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
		Game::gameFlag = 1;
		std::cout << "NEW GAME Button is clicked!" << std::endl;

		return;
	}

	btnY = 40;
	btnW = 75;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
		Game::gameFlag = 2;
		std::cout << "MENU Button is clicked!" << std::endl;

		return;
	}


	btnY = 75;
	btnH = 20;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
		std::cout << "PASS Button is clicked!" << std::endl;

		return;
	}

	btnY = 150;
	btnW = 130;
	btnH = 20;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
		Game::gameFlag = 3;
		std::cout << "CLASSIC Button is clicked!" << std::endl;

		return;
	}
}

bool Game::isRunning() const {
	return Game::running;
}
