#include "Domino.h"

#include <iostream>
#include <random>
#include <algorithm>

Domino::Domino(SDL_Renderer* renderer, Difficulty difficulty, ClassicTileType type, std::string domino)
{
	int maxTileNum = 5;

    if(difficulty == Difficulty::Normal)
    {
		maxTileNum = 7;
	}
    else if(difficulty == Difficulty::Hard)
    {
		maxTileNum = 10;
	}

    for(int i = 0; i < maxTileNum; ++i)
    {
        for(int j = i; j < maxTileNum; ++j)
        {
            m_dominoTiles.push_back(Tile(renderer, std::to_string(i), std::to_string(j), type, domino));
		}
	}

    std::cout << "Domino tiles is created! " << m_dominoTiles.size() << std::endl;
}

void Domino::Shuffle()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(m_dominoTiles.begin(), m_dominoTiles.end(), rng);
    
    m_tileIdx = 0;

    std::cout << "The tiles are shuffled." << std::endl;   
}

Tile Domino::GetNextTile()
{
    if(m_tileIdx >= m_dominoTiles.size())
    {
        m_tileIdx = 0;
    }

    Tile result = m_dominoTiles[m_tileIdx];
    m_tileIdx++;

    return result;
}
