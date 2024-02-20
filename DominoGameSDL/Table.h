#pragma once

#include "Domino.h"

class Table {
public:
	Table();

	std::vector<std::string> tableTiles;

	void addTile(Domino& domino);
};
