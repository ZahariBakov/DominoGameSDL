#pragma once

#include <vector>
#include <string>

class Domino {
public:
	Domino();

	std::vector<std::string> dominoTiles;

	void shuffle();

	std::string giveTile();
	std::string imagePath(std::string name);

private:
	int _tileIdx;
};
