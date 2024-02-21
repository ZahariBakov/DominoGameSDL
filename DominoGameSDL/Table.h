#pragma once

#include "Domino.h"

class Table {
public:
	Table();

	std::vector<Tile> tableTiles;

	void addTile(Domino& domino);
};
