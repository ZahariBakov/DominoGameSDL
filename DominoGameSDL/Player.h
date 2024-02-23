#pragma once

#include "Domino.h"

class Player {
public:
	Player();

	std::vector<Tile> playerTiles;

	void addTiles(Domino& domino);
	void render();
	void removeTile(int idx);

	bool isPossible;
private:
	int _x;
	int _y;
};
