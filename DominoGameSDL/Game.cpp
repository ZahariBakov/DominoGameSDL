#include "Game.h"

#include <iostream>
#include <sstream>

const int matrixX = 300;
const int matrixY = 10;
const int matrixPieceSize = 32;

std::string tableCoordinates;
int tableCoordInt[2]{};

Player* firstPlayer;
Player* secondPlayer;
Table*  table;
Domino* dominoTiles;

Game::Game() {
	Game::window   = NULL;
	Game::renderer = NULL;

	Game::running     = true;
	Game::isInMatrix  = false;

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
	Game::okTex        = NULL;

	Game::newRect       = { 0, 0, 0, 0 };
	Game::menuRect      = { 0, 0, 0, 0 };
	Game::menuTitleRect = { 0, 0, 0, 0 };
	Game::passRect      = { 0, 0, 0, 0 };
	Game::classicRect   = { 0, 0, 0, 0 };
	Game::playerRect    = { 0, 0, 0, 0 };
	Game::playerNumRect = { 0, 0, 0, 0 };
	Game::okRect        = { 0, 0, 0, 0 };
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
				dominoTiles = new Domino(renderer);
				table->setRenderer(renderer);
				//table->printMap();
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

	tempSurfaceText = TTF_RenderText_Blended(font1, "OK", { 255, 255, 255, 255 });
	okTex = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

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

	SDL_QueryTexture(okTex, 0, 0, &tw, &th);
	okRect = { 10, 100, tw, th };

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
		for (int row = 0; row < 20; ++row) {
			for (int col = 0; col < 20; ++col) {
				TextureManager::Instance()->drawTexture("piece", matrixX + (row * matrixPieceSize), matrixY + (col * matrixPieceSize), matrixPieceSize, matrixPieceSize, renderer);
			}
		}

		table->render();
		
		if (Game::gameFlag == 2) {
			SDL_RenderCopy(renderer, menuTex, NULL, &menuRect);
			SDL_RenderCopy(renderer, passTex, NULL, &passRect);
		}
		
		SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
		SDL_RenderCopy(renderer, playerNumTex, NULL, &playerNumRect);

		if (Game::gameFlag == 3) {
			SDL_RenderCopy(renderer, okTex, NULL, &okRect);
		}


		

		if (Game::playerFlag == 1) 
		{
			firstPlayer->render();
		} else if (Game::playerFlag == 2) 
		{
			secondPlayer->render();
		}
	}
	SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);

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
			case SDL_KEYDOWN: {
				if (event.key.keysym.sym == SDLK_LEFT && Game::gameFlag == 3) {
					//table->moveTileInLeft();
					std::cout << "left arrow" << std::endl;
				}
				if (event.key.keysym.sym == SDLK_RIGHT && Game::gameFlag == 3) {
					std::cout << "right arrow" << std::endl;
				}
			}; break;

			default: break;
			}
	}
}

void Game::clean() {
	std::cout << "Cleaning game!\n";

	delete firstPlayer;
	delete secondPlayer;
	delete table;

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
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH)) && Game::gameFlag == 2) {
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

	btnY = 115;
	btnW = 44;

	if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
		(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH)) && Game::gameFlag == 3) {
		Game::playerFlag = nextPlayer(playerFlag);
		Game::gameFlag = 2;
		std::cout << "OK Button is clicked! Next player is: " << playerFlag << std::endl;

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
	int xPos = 0;
	int yPos = 0;

	if (Game::playerFlag == 1 && Game::gameFlag == 2) {
		for (int i = 0; i < firstPlayer->playerTiles.size(); ++i) {
			btnX = 150 + i * 100;

			if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
				(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
				Game::isSeleckted(i);
				std::cout << "First player tile is clicked " << firstPlayer->playerTiles[i].getFirst() << "-" 
					<< firstPlayer->playerTiles[i].getSecond() << std::endl;
			}
		}	

		if (!firstPlayer->isPossible) {
			if ((xDown > matrixX && xDown < (matrixX + matrixPieceSize * 20)) && (xUp > matrixX && xUp < (matrixX + matrixPieceSize * 20)) &&
				(yDown > matrixY && yDown < (matrixY + matrixPieceSize * 20)) && (yUp > matrixY && yUp < (matrixY + matrixPieceSize * 20))) {
				Game::isInMatrix = true;
				std::cout << "First player click in matrix" << std::endl;
			}

			if (Game::isInMatrix) {
				for (int i = 0;i < firstPlayer->playerTiles.size(); ++i) {
					if (firstPlayer->playerTiles[i].isSelected == true) {
						firstPlayer->isPossible = table->checkForPlacement(firstPlayer->playerTiles[i], xDown, yDown, xUp, yUp);
						if (firstPlayer->isPossible) 
						{
							firstPlayer->removeTile(i);
							Game::gameFlag = 3;	
							firstPlayer->isPossible = false;
						}
					}
				}
				Game::isInMatrix = false;
			}		
		}
		
	}
	else if (Game::playerFlag == 2 && Game::gameFlag == 2) {
		for (int i = 0; i < secondPlayer->playerTiles.size(); ++i) {
			btnX = 150 + i * 100;

			if ((xDown > btnX && xDown < (btnX + btnW)) && (xUp > btnX && xUp < (btnX + btnW)) &&
				(yDown > btnY && yDown < (btnY + btnH)) && (yUp > btnY && yUp < (btnY + btnH))) {
				Game::isSeleckted(i);
				std::cout << "Second player tile is clicked " << secondPlayer->playerTiles[i].getFirst() 
					<< "-" << secondPlayer->playerTiles[i].getSecond() << std::endl;
			}
		}

		if (!secondPlayer->isPossible) {
			if ((xDown > matrixX && xDown < (matrixX + matrixPieceSize * 20)) && (xUp > matrixX && xUp < (matrixX + matrixPieceSize * 20)) &&
				(yDown > matrixY && yDown < (matrixY + matrixPieceSize * 20)) && (yUp > matrixY && yUp < (matrixY + matrixPieceSize * 20))) {
				Game::isInMatrix = true;
				std::cout << "Second player click in matrix" << std::endl;
			}

			if (Game::isInMatrix) {
				for (int i =0; i < secondPlayer->playerTiles.size(); ++i) {
					if (secondPlayer->playerTiles[i].isSelected == true) {
						secondPlayer->isPossible = table->checkForPlacement(secondPlayer->playerTiles[i], xDown, yDown, xUp, yUp);
						if (secondPlayer->isPossible)
						{
							secondPlayer->removeTile(i);
							Game::gameFlag = 3;
							secondPlayer->isPossible = false;
						}
					}
				}
				Game::isInMatrix = false;
			}		
		}	
	}
}

bool Game::isSeleckted(int idx) const
{
	if (Game::playerFlag == 1) {
		for (auto& tile : firstPlayer->playerTiles) {
			tile.isSelected = false;
		}
		firstPlayer->playerTiles[idx].isSelected = true;
		return true;
	} else if (Game::playerFlag == 2) 
	{
		for (auto& tile : secondPlayer->playerTiles) {
			tile.isSelected = false;
		}
		secondPlayer->playerTiles[idx].isSelected = true;
		return true;
	}

	return false;
}

bool Game::isRunning() const {
	return Game::running;
}

void Game::startNewGame() {
	dominoTiles->shuffle();

	if (firstPlayer->playerTiles.size() > 0) {
		firstPlayer->playerTiles.clear();
		secondPlayer->playerTiles.clear();
		table->clear();
		table->createMap();
	}


	firstPlayer->addTiles(*dominoTiles);
	std::cout << "First player have tiles" << std::endl;
	secondPlayer->addTiles(*dominoTiles);
	std::cout << "Second player have tiles" << std::endl;

	Tile tmpTile = dominoTiles->giveTile();
	table->addTile(tmpTile);
	std::cout << "Table have tile" << std::endl;
}

int Game::nextPlayer(int currPlayer) {
	if (currPlayer == 1) {
		return 2;
	}
	
	return 1;
}

void Game::CoordinatesToInt() {
	std::stringstream stream(tableCoordinates);
	std::string temp;
	int idx = 0;

	while (std::getline(stream, temp, ',')) {
		int value = std::stoi(temp);
		tableCoordInt[idx] = value;
		++idx;
	}
}

bool Game::playerTileClicked(int idx) const {
	if (true) {

		std::cout << "First player current tile is " << firstPlayer->playerTiles[idx].getFirst() << " " 
			<< firstPlayer->playerTiles[idx].getSecond() << std::endl;

		if ((firstPlayer->playerTiles[idx].getFirst() == table->firstFree) || (firstPlayer->playerTiles[idx].getFirst() == table->secondFree) ||
			(firstPlayer->playerTiles[idx].getSecond() == table->firstFree) || (firstPlayer->playerTiles[idx].getSecond() == table->secondFree)) {
			std::cout << "Is posible" << std::endl;
			return true;
		}
	}
	else {
		for (auto &tile : secondPlayer->playerTiles) {
			tile.isSelected = false;
		}
		secondPlayer->playerTiles[idx].isSelected = true;

		std::cout << "Second player current tile is " << secondPlayer->playerTiles[idx].getFirst() << " "
			<< secondPlayer->playerTiles[idx].getSecond() << std::endl;

		if ((secondPlayer->playerTiles[idx].getFirst() == table->firstFree) || (secondPlayer->playerTiles[idx].getFirst() == table->secondFree) ||
			(secondPlayer->playerTiles[idx].getSecond() == table->firstFree) || (secondPlayer->playerTiles[idx].getSecond() == table->secondFree)) {
			std::cout << "Is posible" << std::endl;
			return true;
		}
	}

	return false;
}
