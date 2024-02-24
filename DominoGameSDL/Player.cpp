#include "Player.h"

#include <iostream>

Player::Player() {
	this->isPossible = false;
	_x = 150;
	_y = 670;
	playedTiles = 0;
}

void Player::addTiles(Domino& domino) {
	for (int i = 0; i < 10; ++i) {
		this->playerTiles.push_back(domino.giveTile());
		playerTiles[i].setPosition(_x + i * 100, _y);
	}

	std::cout << "Player add tiles!" << std::endl;
}

void Player::render()
{
	for (int i = 0; i < playerTiles.size(); ++i) {
		playerTiles[i].tileRender();
	}
}

void Player::removeTile(int idx) 
{
	//playerTiles.erase(playerTiles.begin() + idx);
	playerTiles[idx].setValues();
	playedTiles++;
}
