#pragma once

#include "Tile.h"

#include <vector>

class Domino {
public:
	Domino(SDL_Renderer* renderer);

	std::vector<Tile> dominoTiles;

	void shuffle();

	Tile giveTile();

private:
	int _tileIdx;
};
