#pragma once

#include "Domino.h"
#include "TextureManager.h"

#include <map>
#include<string>

class Table {
public:
	Table();

	//std::vector<Tile> tableTiles;
	//std::vector<std::string> tileYX;
	Box tableBox[20][20];

	void addTile(Tile& newTile, int xPos = 9, int yPos = 9);

	std::string firstFree;
	std::string secondFree;

	//std::string map[20][20];
	std::map<std::string, int> firstFreePos;
	std::map<std::string, int> secondFreePos;

	//void printMap() const;
	bool checkForPlacement(Tile playerTile, int xDown, int yDown, int xUp, int yUp);
	//void moveTileInLeft();
	void createMap();
	void render();
	void setRenderer(SDL_Renderer* renderer);
	void clear();

private:
	bool firstTurn = true;
	SDL_Renderer* _renderer;
};
