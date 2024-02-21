#pragma once

#include "Domino.h"

class Player {
public:
	Player();

	std::vector<Tile> playerTiles;

	void addTiles(Domino& domino);
};
