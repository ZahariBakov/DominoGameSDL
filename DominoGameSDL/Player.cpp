#include "Player.h"

#include <iostream>

Player::Player() {}

void Player::addTiles(Domino& domino) {
	for (int i = 0; i < 10; ++i) {
		this->playerTiles.push_back(domino.giveTile());
	}

	std::cout << "Player add tiles!" << std::endl;
}
