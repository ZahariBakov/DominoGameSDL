#include "Tile.h"

#include <iostream>

Tile::Tile() {
	this->isSelected = false;
	_tileX = _tileY = 0;
}

Tile::Tile(SDL_Renderer* ren, std::string first, std::string second, int tileX, int tileY, int type, std::string domino)
	: _first(ren, first, tileX, tileY, type, domino), _second(ren, second, tileX + 32, tileY, type, domino) {

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
	if (_first.getX() == _second.getX() - 32) {
		std::cout << "tile is horizontal" << std::endl;
		
		_second.Box::setPosition(_second.getX() - 32, _second.getY() + 32);
	}
	else if (_first.getY() == _second.getY() - 32) {
		std::cout << "tile is upper head" << std::endl;
		_second.Box::setPosition(_second.getX() - 64, _second.getY());
	}
	else if (_first.getX() == _second.getX() + 32) {
		std::cout << "tile is flip horizontal" << std::endl;
		_second.Box::setPosition(_second.getX() - 32, _second.getY() - 32);
	}
	else if (_first.getY() == _second.getY() + 32) {
		std::cout << "tile is down head" << std::endl;
		_second.Box::setPosition(_second.getX(), _second.getY());
	}
}

void Tile::setPosition(int x, int y)
{
	_tileX = x;
	_tileY = y;
	_first.setPosition(x, y);
	_second.setPosition(x + 32, y);
}

void Tile::setValues()
{
	_first.setValue("10");
	_second.setValue("10");
}
