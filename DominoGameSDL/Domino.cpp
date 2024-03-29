#include "Domino.h"

#include <iostream>
#include <random>
#include <algorithm>

Domino::Domino(SDL_Renderer* renderer, int difficulty, int type, std::string domino) {
	this->_tileIdx = 0;
	int maxTileNum = 5;

	if (difficulty == 1) {
		maxTileNum = 7;
	}
	else if (difficulty == 2) {
		maxTileNum = 10;
	}

	for (int i = 0; i < maxTileNum; ++i) {
		for (int j = i; j < maxTileNum; ++j) {
			dominoTiles.push_back(Tile(renderer, std::to_string(i), std::to_string(j), 0, 0, type, domino));
		}
	}

	std::cout << "Domino tiles is created! " << dominoTiles.size() << std::endl;
}

void Domino::shuffle() {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(dominoTiles.begin(), dominoTiles.end(), rng);

	this->_tileIdx = 0;

    std::cout << "The tiles are shuffled." << std::endl;   
}

Tile Domino::giveTile() {
	Tile result = dominoTiles[this->_tileIdx];
	this->_tileIdx++;

	return result;
}
