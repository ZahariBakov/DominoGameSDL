#pragma once

#include<string>

class Tile {
public:
	Tile();
	Tile(std::string first, std::string second);

	std::string getFirst() const;
	std::string getSecond() const;

	bool isSelected;

private:
	std::string _first;
	std::string _second;
};
