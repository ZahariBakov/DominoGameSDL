#pragma once

#include "Tile.h"

#include <vector>

class Domino {
public:
	Domino(SDL_Renderer* renderer, int difficulty, int type, std::string domino);

	std::vector<Tile> dominoTiles;

	void shuffle();

	Tile giveTile();

private:
	int _tileIdx;
};
