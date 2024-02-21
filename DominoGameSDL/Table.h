#pragma once

#include "Domino.h"

class Table {
public:
	Table();

	std::vector<Tile> tableTiles;

	void addTile(Domino& domino);

	std::string firstFree;
	std::string secondFree;

	char map[20][20];

	void printMap();
};
