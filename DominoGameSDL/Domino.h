#pragma once

#include "Tile.h"

#include <vector>

class Domino {
public:
	Domino();

	std::vector<Tile> dominoTiles;

	void shuffle();

	Tile giveTile();
	std::string imagePath(std::string name);

private:
	int _tileIdx;
};
