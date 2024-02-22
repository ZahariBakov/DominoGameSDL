#pragma once

#include "Domino.h"
#include "TextureManager.h"

#include <map>
#include<string>

class Table {
public:
	Table();

	std::vector<Tile> tableTiles;

	void addTile(Tile& newTile, int xPos = 9, int yPos = 9);

	std::string firstFree;
	std::string secondFree;

	std::string map[20][20];
	std::map<std::string, int> firstFreePos;
	std::map<std::string, int> secondFreePos;

	void printMap() const;
	void checkForPlacement(Tile playerTile, int xDown, int yDown, int xUp, int yUp, int &xPos, int &yPos);

	void createMap();
};
