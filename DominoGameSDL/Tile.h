#pragma once

#include<string>
#include "Box.h"

class Tile {
public:
	Tile();
	Tile(SDL_Renderer* ren, std::string first, std::string second, int tileX, int tileY);

	std::string getFirst() const;
	std::string getSecond() const;

	void tileRender();
	void rotate();
	void setPosition(int x, int y);
	bool isSelected;

private:
	Box _first;
	Box _second;
	int _tileX;
	int _tileY;
};
