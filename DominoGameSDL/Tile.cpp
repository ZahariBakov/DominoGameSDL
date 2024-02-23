#include "Tile.h"

#include <iostream>

Tile::Tile() {
	this->isSelected = false;
	_tileX = _tileY = 0;
}

Tile::Tile(SDL_Renderer* ren, std::string first, std::string second, int tileX, int tileY) 
	: _first(ren, first, tileX, tileY), _second(ren, second, tileX + 32, tileY) {

	this->isSelected = false;
	_tileX = tileX;
	_tileY = tileY;
}

std::string Tile::getFirst() const {
	return this->_first.getValue();
}

std::string Tile::getSecond() const {
	return this->_second.getValue();
}

void Tile::tileRender() {
	_first.render();
	_second.render();
}

void Tile::rotate() {
	//TODO...
}

void Tile::setPosition(int x, int y)
{
	_tileX = x;
	_tileY = y;
	_first.setPosition(x, y);
	_second.setPosition(x + 32, y);
}
