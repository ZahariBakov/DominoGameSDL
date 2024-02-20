#pragma once

#include "Domino.h"

class Player {
public:
	Player();

	std::vector<std::string> playerTiles;

	void addTiles(Domino& domino);
};
