#include "Table.h"

#include <iostream>

Table::Table() {}

void Table::addTile(Domino& domino) {
	std::string tileName = domino.giveTile();
	std::cout << "Tile name is: " << tileName << std::endl;

	std::cout << "Vector size: " << tableTiles.size() << std::endl;
	this->tableTiles.push_back(domino.giveTile());
}
