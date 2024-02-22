#include "Game.h"

#include <iostream>

Player* firstPlayer;
Player* secondPlayer;
Table*  table;

Game::Game() {
	Game::window   = NULL;
	Game::renderer = NULL;

	Game::running = true;

	Game::mouseDownX = 0;
	Game::mouseDownY = 0;
	Game::gameFlag   = 0;
	Game::playerFlag = 1;

	Game::newTex       = NULL;
	Game::menuTex      = NULL;
	Game::menuTitleTex = NULL;
	Game::passTex      = NULL;
	Game::classicTex   = NULL;
	Game::playerTex    = NULL;
	Game::playerNumTex = NULL;

	Game::newRect       = { 0, 0, 0, 0 };
	Game::menuRect      = { 0, 0, 0, 0 };
	Game::menuTitleRect = { 0, 0, 0, 0 };
	Game::passRect      = { 0, 0, 0, 0 };
	Game::classicRect   = { 0, 0, 0, 0 };
	Game::playerRect    = { 0, 0, 0, 0 };
	Game::playerNumRect = { 0, 0, 0, 0 };
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
				TextureManager::Instance()->loadTexture("assets/piece.png", "piece", renderer);

				firstPlayer  = new Player();
				secondPlayer = new Player();
				table = new Table();
				table->printMap();
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

	TTF_Font* font1 = TTF_OpenFont("fonts/segoepr.ttf", 28);
	TTF_Font* font2 = TTF_OpenFont("fonts/segoepr.ttf", 72);

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

	tempSurfaceText = TTF_RenderText_Blended(font1, "PLAYER", { 255, 255, 255, 255 });
	playerTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	
	std::string tmp = std::to_string(Game::playerFlag);
	char const* playerNum = tmp.c_str();

	tempSurfaceText = TTF_RenderText_Blended(font1, playerNum, { 255, 255, 255, 255 });
	playerNumTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

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

	SDL_QueryTexture(playerTex, 0, 0, &tw, &th);
	playerRect = { 10, wh - 110, tw, th };

	SDL_QueryTexture(playerNumTex, 0, 0, &tw, &th);
	playerNumRect = { 140, wh - 110, tw, th };

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
		TextureManager::Instance()->drawTexture("welcome", 0, 0, ww, wh, renderer);
		SDL_RenderCopy(renderer, newTex, NULL, &newRect);

	}
	else if (Game::gameFlag == 1) {
		SDL_RenderCopy(renderer, menuTitleTex, NULL, &menuTitleRect);
		SDL_RenderCopy(renderer, classicTex, NULL, &classicRect);
	}
	else {
		int x = 300;
		int y = 10;
		for (int row = 0; row < 20; ++row) {
			for (int col = 0; col < 20; ++col) {
				TextureManager::Instance()->drawTexture("piece", x + (row * 32), y + (col * 32), 32, 32, renderer);
			}
		}
		
		SDL_RenderCopy(renderer, menuTex, NULL, &menuRect);
		SDL_RenderCopy(renderer, passTex, NULL, &passRect);
		SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
		SDL_RenderCopy(renderer, playerNumTex, NULL, &playerNumRect);

		for (int i = 0; i < table->tableTiles.size(); ++i) {
			std::string tileName = table->tableTiles[i].getFirst() + table->tableTiles[i].getSecond();
			TextureManager::Instance()->loadTexture(dominoTiles.imagePath(tileName).c_str(), tileName, renderer);
			TextureManager::Instance()->drawTexture(tileName, x + 9 * 32 - 16, y + 9 * 32 + 16, 64, 32, renderer, 90);
		}

		if (Game::playerFlag == 1) {
			for (int i = 0; i < firstPlayer->playerTiles.size(); ++i) {
				int x = 150 + i * 100;

				std::string tileName = firstPlayer->playerTiles[i].getFirst() + firstPlayer->playerTiles[i].getSecond();
				TextureManager::Instance()->loadTexture(dominoTiles.imagePath(tileName).c_str(), tileName, renderer);
				TextureManager::Instance()->drawTexture(tileName, x, wh - 50, 64, 32, renderer);
			}
		}

		if (Game::playerFlag == 2) {
			for (int i = 0; i < secondPlayer->playerTiles.size(); ++i) {
				int x = 150 + i * 100;

				std::string tileName = secondPlayer->playerTiles[i].getFirst() + secondPlayer->playerTiles[i].getSecond();
				TextureManager::Instance()->loadTexture(dominoTiles.imagePath(tileName).c_str(), tileName, renderer);
				TextureManager::Instance()->drawTexture(tileName, x, wh - 50, 64, 32, renderer);
			}
		}
	}
	//SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);

	SDL_RenderPresent(renderer);
}

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
	int btnY = 23;
	int btnW = 170;
	int btnH = 23;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH)) && Game::gameFlag == 0) {
		Game::gameFlag = 1;
		std::cout << "NEW GAME Button is clicked!" << std::endl;

		return;
	}

	btnY = 54;
	btnW = 90;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH)) && Game::gameFlag > 0) {
		Game::gameFlag = 1;
		std::cout << "MENU Button is clicked!" << std::endl;

		return;
	}

	btnY = 84;
	btnW = 80;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH)) && Game::gameFlag == 2) {
		Game::playerFlag = nextPlayer(playerFlag);

		std::cout << "PASS Button is clicked! Next player is: " << playerFlag << std::endl;

		return;
	}

	btnY = 163;
	btnW = 130;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH)) && Game::gameFlag == 1) {
		Game::startNewGame();
		Game::gameFlag = 2;

		std::cout << "CLASSIC Button is clicked!" << std::endl;

		return;
	}

	btnX = 150;
	btnY = wh - 50;
	btnW = 64;
	btnH = 32;

	if (Game::playerFlag == 1 && Game::gameFlag == 2) {
		//std::cout << "First player tiles size: " << firstPlayer->playerTiles.size() << std::endl;
		for (int i = 0; i < firstPlayer->playerTiles.size(); ++i) {
			btnX = 150 + i * 100;

			if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
				(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
				Game::playerTileClicked(i);
				std::cout << "First player tile is clicked" << std::endl;
			}
		}	

		for (auto tile : firstPlayer->playerTiles) {
			if (tile.isSelected == true) {
				table->checkForPlacement(tile, xDown, yDown, xUp, yUp);
			}
		}
	}
	else if (Game::playerFlag == 2 && Game::gameFlag == 2) {
		//std::cout << "Second player tiles size: " << secondPlayer->playerTiles.size() << std::endl;
		for (int i = 0; i < secondPlayer->playerTiles.size(); ++i) {
			btnX = 150 + i * 100;

			if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
				(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
				Game::playerTileClicked(i);
				std::cout << "Second player tile is clicked" << std::endl;
			}
		}

		for (auto tile : secondPlayer->playerTiles) {
			if (tile.isSelected == true) {
				table->checkForPlacement(tile, xDown, yDown, xUp, yUp);
			}
		}
	}
}

bool Game::isRunning() const {
	return Game::running;
}

void Game::startNewGame() {
	dominoTiles.shuffle();

	if (firstPlayer->playerTiles.size() > 0) {
		firstPlayer->playerTiles.clear();
		secondPlayer->playerTiles.clear();
		table->tableTiles.clear();
	}


	firstPlayer->addTiles(dominoTiles);
	std::cout << "First player have tiles" << std::endl;
	secondPlayer->addTiles(dominoTiles);
	std::cout << "Second player have tiles" << std::endl;

	table->addTile(dominoTiles);
	std::cout << "Table have tile" << std::endl;
}

int Game::nextPlayer(int currPlayer) {
	if (currPlayer == 1) {
		return 2;
	}
	
	return 1;
}

void Game::playerTileClicked(int idx) {
	if (Game::playerFlag == 1) {
		for (auto tile : firstPlayer->playerTiles) {
			tile.isSelected = false;
		}
		firstPlayer->playerTiles[idx].isSelected = true;
		std::cout << "First player current tile is " << firstPlayer->playerTiles[idx].getFirst() << " " 
			<< firstPlayer->playerTiles[idx].getSecond() << std::endl;

		if (firstPlayer->playerTiles[idx].getFirst() == table->firstFree) {
			std::cout << "The first piece of the first player's tile is the same as the first free piece on the table" << std::endl;
		}
		else if (firstPlayer->playerTiles[idx].getFirst() == table->secondFree) {
			std::cout << "The first piece of the first player's tile is the same as the second free piece on the table" << std::endl;
		}
		else if (firstPlayer->playerTiles[idx].getSecond() == table->firstFree) {
			std::cout << "The second piece of the first player's tile is the same as the first free piece on the table" << std::endl;
		}
		else if (firstPlayer->playerTiles[idx].getSecond() == table->secondFree) {
			std::cout << "The second piece of the first player's tile is the same as the second free piece on the table" << std::endl;
		}
	}
	else {
		for (auto tile : secondPlayer->playerTiles) {
			tile.isSelected = false;
		}
		secondPlayer->playerTiles[idx].isSelected = true;
		std::cout << "Second player current tile is " << secondPlayer->playerTiles[idx].getFirst() << " "
			<< secondPlayer->playerTiles[idx].getSecond() << std::endl;

		if (secondPlayer->playerTiles[idx].getFirst() == table->firstFree) {
			std::cout << "The first piece of the second player's tile is the same as the first free piece on the table" << std::endl;
		}
		else if (secondPlayer->playerTiles[idx].getFirst() == table->secondFree) {
			std::cout << "The first piece of the second player's tile is the same as the second free piece on the table" << std::endl;
		}
		else if (secondPlayer->playerTiles[idx].getSecond() == table->firstFree) {
			std::cout << "The second piece of the second player's tile is the same as the first free piece on the table" << std::endl;
		}
		else if (secondPlayer->playerTiles[idx].getSecond() == table->secondFree) {
			std::cout << "The second piece of the second player's tile is the same as the second free piece on the table" << std::endl;
		}
	}
}
