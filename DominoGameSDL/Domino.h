#pragma once

#include "Tile.h"
#include "Enums.h"

#include <vector>

class Domino
{
public:
    Domino(SDL_Renderer* renderer, Difficulty difficulty, ClassicTileType type, std::string domino);

    void Shuffle();

    auto GetNextTile() -> Tile;

private:
    int m_tileIdx = 0;
    std::vector<Tile> m_dominoTiles;
};
