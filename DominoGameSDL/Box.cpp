#include "Box.h"

int side = 32;

Box::Box() {
	this->_value = "*";
	this->_x = 0;
	this->_y = 0;
	this->_renderer = nullptr;
}

Box::Box(SDL_Renderer* renderer, std::string value, int x, int y) {
	this->_value = value;
	this->_x = x;
	this->_y = y;
	this->_renderer = renderer;
	std::string path = "assets/" + value + ".png";

	TextureManager::Instance()->loadTexture(path.c_str(), value, _renderer);
	
}

std::string Box::getValue() const {
	return _value;
}

int Box::getY() const {
	return _y;
}

int Box::getX() const {
	return _x;
}

void Box::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Box::setValue(std::string value) 
{
	_value = value;
}

void Box::render() const {
	if (_value == "*") {
		return;
	}

	TextureManager::Instance()->drawTexture(_value, _x, _y, side, side, _renderer);
}

void Box::setRenderer(SDL_Renderer* renderer) 
{
	_renderer = renderer;
}
