#include "Player.h"

Player::Player(Domino& domino) {
	for (int i = 0; i < 10; ++i) {
		this->playerTiles.push_back(domino.giveTile());
	}
}