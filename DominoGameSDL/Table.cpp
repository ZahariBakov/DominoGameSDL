#include "Table.h"

#include <iostream>

Table::Table() {}

void Table::addTile(Domino& domino) {
	Tile tile = domino.giveTile();
	std::cout << "Tile name is: " << tile.getFirst() << " " << tile.getSecond() << std::endl;

	std::cout << "Vector size: " << tableTiles.size() << std::endl;
	this->tableTiles.push_back(tile);
}
