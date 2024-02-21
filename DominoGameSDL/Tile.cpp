#include "Tile.h"

Tile::Tile() {}

Tile::Tile(std::string first, std::string second) : _first(first), _second(second) {}

std::string Tile::getFirst() const {
	return this->_first;
}

std::string Tile::getSecond() const {
	return this->_second;
}
