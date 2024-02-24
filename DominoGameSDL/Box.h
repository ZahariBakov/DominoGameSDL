#pragma once

#include "TextureManager.h"

#include <string>

class Box {
public:
	Box();
	Box(SDL_Renderer* renderer, std::string value, int x, int y);

	std::string getValue() const;
	int getY() const;
	int getX() const;

	void setPosition(int x, int y);
	void setValue(std::string value);
	void render() const;
	void setRenderer(SDL_Renderer* renderer);


private:
	std::string _value;
	int _x;
	int _y;
	SDL_Renderer* _renderer;
};
