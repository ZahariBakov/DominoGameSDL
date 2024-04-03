#include "PlayerTiles.h"
#include <iostream>
#include <sstream>

void PlayerTiles::Init(Domino &domino, Difficulty difficulty)
{
    static const auto INITIAL_PLAYER_TILE_POS = Vector2D{1300, 10};

    m_playerTilePos = INITIAL_PLAYER_TILE_POS;
    int tileNum = 7;

    if(difficulty == Difficulty::Normal)
    {
        tileNum = 13;
    }
    else if(difficulty == Difficulty::Hard)
    {
        tileNum = 27;
    }

    for(int i = 0; i < tileNum; ++i)
    {
        if((i % 3) == 0)
        {
            m_playerTilePos.y += 40;
            m_playerTilePos.x -= 300;
        }

        m_playerTiles.push_back(domino.GetNextTile());
        m_playerTiles[i].SetHorizontal(Vector2D(m_playerTilePos.x, m_playerTilePos.y));
        m_playerTilePos.x += 100;
    }

    std::cout << "Player add " << tileNum << " tiles!" << std::endl;
}

void PlayerTiles::Remove(int idx)
{
    Hide(idx);
    m_playedTile++;
}

void PlayerTiles::Hide(int idx)
{
    m_playerTiles[idx].SetVisible(false);
}

void PlayerTiles::Show(int idx, std::string first, std::string second)
{
    m_playerTiles[idx].SetValues(first, second);
}

void PlayerTiles::ResetPlayed()
{
    m_playedTile = 0;
}

void PlayerTiles::ClearPlayer()
{
    m_playerTiles.clear();
}

Tile& PlayerTiles::GetCurrent(int idx)
{
    return m_playerTiles[idx];
}

int PlayerTiles::GetSize() const
{
    return int(m_playerTiles.size());
}

int PlayerTiles::GetPlayed() const
{
    return m_playedTile;
}

Vector2D PlayerTiles::GetCurrentPos(int idx) const
{
    return Vector2D(m_playerTiles[idx].GetPos());
}

void PlayerTiles::SetIsPossibleToAddCurrent(bool state)
{
    m_isPossible = state;
}

bool PlayerTiles::IsPossibleToAddCurrent() const
{
    return m_isPossible;
}

void PlayerTiles::UnselectAll()
{
    for(auto& tile : m_playerTiles)
    {
        tile.SetIsSelected(false);
    }
}

void PlayerTiles::SelectCurrent(int idx)
{
    m_playerTiles[idx].SetIsSelected(true);
}

std::string PlayerTiles::WritePlayerTiles() const
{
    std::string data;

    for(const auto tile : m_playerTiles)
    {
        data += tile.GetFirst() + "-";
        data += tile.GetSecond() + "-";
        data += std::to_string(tile.GetPos().x) + "-";
        data += std::to_string(tile.GetPos().y) + "-";
        data += std::to_string(tile.IsVisible()) + " ";
    }

    data += std::to_string(GetPlayed()) + " ";

    return data;
}

void PlayerTiles::SetPlayerTilesData(SDL_Renderer* ren, std::vector<std::string> playerData, ClassicTileType type, std::string domino)
{
    std::string first;
    std::string second;
    std::string token;
    Vector2D tilePos;

    m_playedTile = stoi(playerData.back());
    playerData.pop_back();

    for(const auto tile : playerData)
    {
        std::istringstream istr(tile);
        std::getline(istr, token, '-');
        first = token;
        std::getline(istr, token, '-');
        second = token;
        Tile currentTile = Tile(ren, first, second, type, domino);
        std::getline(istr, token, '-');
        tilePos.x = std::stoi(token);
        std::getline(istr, token, '-');
        tilePos.y = std::stoi(token);
        currentTile.SetHorizontal(tilePos);
        std::getline(istr, token, '-');

        if(token == "0")
        {
            currentTile.SetVisible(false);
        }
        m_playerTiles.push_back(currentTile);
    }
}

void PlayerTiles::Render()
{
    for(size_t i = 0; i < m_playerTiles.size(); ++i)
    {
        if(m_playerTiles[i].IsVisible())
        {
            m_playerTiles[i].Render();
        }
    }
}
