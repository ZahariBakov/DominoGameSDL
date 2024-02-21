#include "Table.h"

#include <iostream>

Table::Table() {
	this->createMap();
}

void Table::addTile(Domino& domino) {
	Tile tile = domino.giveTile();
	this->tableTiles.push_back(tile);

	std::cout << "Table add tile." << std::endl;
}

void Table::printMap() {
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
			map[row][col] = '*';
		}
	}

	std::cout << "map is created" << std::endl;
}