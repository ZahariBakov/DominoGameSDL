#include "Domino.h"

#include <iostream>
#include <random>
#include <algorithm>

Domino::Domino() {
	this->_tileIdx = 0;
	std::string currentTiles;

	for (int i = 0; i < 7; ++i) {
		for (int j = i; j < 7; ++j) {
			currentTiles = std::to_string(i) + std::to_string(j);
			dominoTiles.push_back(currentTiles);
		}
	}

	std::cout << "Domino tiles is created!" << std::endl;
}

void Domino::shuffle() {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 rng(rd());

    // Shuffle the vector using std::shuffle
    std::shuffle(dominoTiles.begin(), dominoTiles.end(), rng);

    std::cout << "The tiles are shuffled." << std::endl;
    
}

std::string Domino::giveTile() {
	std::string result = dominoTiles[this->_tileIdx];
	this->_tileIdx++;

	return result;
}

std::string Domino::imagePath(std::string name) {
	std::string result;

	result = "assets/classic/" + name + ".png";

	return result;
}
