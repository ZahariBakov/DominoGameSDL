#include "Player.h"

#include <iostream>

Player::Player() {
	this->isPossible = false;
}

void Player::addTiles(Domino& domino) {
	for (int i = 0; i < 10; ++i) {
		this->playerTiles.push_back(domino.giveTile());
	}

	std::cout << "Player add tiles!" << std::endl;
}

Tile Player::removeTile(int idx) {
	Tile currTile = playerTiles[idx];
	playerTiles.erase(playerTiles.begin() + idx);

	return currTile;
}
