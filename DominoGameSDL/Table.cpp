#include "Table.h"

#include <iostream>

const int matrixX = 300;
const int matrixY = 10;
const int matrixPieceSize = 32;

Table::Table() {
	this->createMap();
}

void Table::addTile(Domino& domino) {
	Tile tile = domino.giveTile();
	
	if (this->tableTiles.size() == 0) {
		this->firstFree = tile.getFirst();
		this->secondFree = tile.getSecond();
		map[9][9] = firstFree;
		map[10][9] = secondFree;
		firstFreePos["x"] = 9;
		firstFreePos["y"] = 9;
		secondFreePos["y"] = 10;
		secondFreePos["x"] = 9;
	}

	this->tableTiles.push_back(tile);
	std::cout << "First free piece of tile is: " << firstFree << std::endl;
	std::cout << "Second free piece of tile is: " << secondFree << std::endl;
	std::cout << "Table add tile." << std::endl;
	printMap();
}

void Table::printMap() const {
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			std::cout << map[row][col];
		}
		std::cout << std::endl;
	}
}

void Table::checkForPlacement(Tile playerTile, int xDown, int yDown, int xUp, int yUp) {
	int xPress =   (xDown - matrixX) / matrixPieceSize;
	int yPress =   (yDown - matrixY) / matrixPieceSize;
	int xUnpress = (xUp - matrixX)   / matrixPieceSize;
	int yUnpress = (yUp - matrixY)   / matrixPieceSize;

	std::cout << "down - up x: " << xPress << "-" << xUnpress << std::endl;
	std::cout << "down - up y: " << yPress << "-" << yUnpress << std::endl;

	if (xPress == xUnpress && yPress == yUnpress) {
		if (playerTile.getFirst() == firstFree || playerTile.getSecond() == firstFree) {
			if ((xPress == firstFreePos["x"] - 1 || xPress == firstFreePos["x"] + 1 || xPress == firstFreePos["x"]) && (yPress == firstFreePos["y"] == 1) ||
				((yPress == firstFreePos["y"] - 1 || yPress == firstFreePos["y"] + 1 || yPress == firstFreePos["y"] == 1) && (xPress == firstFreePos["x"]))) {
				std::cout << "can add tile here: [" << xPress << "][" << yPress << "]" << std::endl;
			}
		}
		else {
			if ((xPress == secondFreePos["x"] - 1 || xPress == secondFreePos["x"] + 1 || xPress == secondFreePos["x"]) && (yPress == secondFreePos["y"] == 1) ||
				((yPress == secondFreePos["y"] - 1 || yPress == secondFreePos["y"] + 1 || yPress == secondFreePos["y"] == 1) && (xPress == secondFreePos["x"]))) {
				std::cout << "can add tile here: [" << xPress << "][" << yPress << "]" << std::endl;
			}
		}
	}

	std::cout << "first free is with pos: "  << firstFreePos["x"] << " "  << firstFreePos["y"] << std::endl;
	std::cout << "second free is with pos: " << secondFreePos["x"] << " " << secondFreePos["y"] << std::endl;
}

void Table::createMap() {
	for (int row = 0; row < 20; ++row) {
		for (int col = 0; col < 20; ++col) {
			map[row][col] = "*";
		}
	}

	std::cout << "map is created" << std::endl;
}