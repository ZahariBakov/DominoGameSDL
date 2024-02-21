#include "Table.h"

#include <iostream>

Table::Table() {
	this->createMap();
}

void Table::addTile(Domino& domino) {
	Tile tile = domino.giveTile();
	
	if (this->tableTiles.size() == 0) {
		this->firstFree = tile.getFirst();
		this->secondFree = tile.getSecond();

	}

	this->tableTiles.push_back(tile);
	std::cout << "First free piece of tile is: " << firstFree << std::endl;
	std::cout << "Second free piece of tile is: " << secondFree << std::endl;
	std::cout << "Table add tile." << std::endl;
}

void Table::printMap() const {
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			std::cout << map[row][col];
		}
		std::cout << std::endl;
	}
}

void Table::createMap() {
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			map[row][col] = "*";
		}
	}

	std::cout << "map is created" << std::endl;
}