#pragma once

#include "Domino.h"

class Player {
public:
	Player();

	std::vector<Tile> playerTiles;

	void addTiles(Domino& domino, int difficulty);
	void render();
	void removeTile(int idx);
	void rotate(int idx);
	void addWin();
	void resetWin();

	int getWin() const;

	int playedTiles;

	bool isPossible;
private:
	int _x;
	int _y;
	int _win;
};
