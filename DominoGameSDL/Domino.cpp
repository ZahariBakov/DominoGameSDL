#include "Domino.h"

#include <iostream>

Domino::Domino() {
	std::string currentTiles;

	for (int i = 0; i < 7; ++i) {
		for (int j = i; j < 7; ++j) {
			currentTiles = std::to_string(i) + std::to_string(j);
			dominoTiles.push_back(currentTiles);
		}
	}

	std::cout << "Domino tiles is created!" << std::endl;
}
