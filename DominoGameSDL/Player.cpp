#include "Player.h"
#include "GameConstants.h"

#include <iostream>

void Player::AddTiles(Domino& domino, Difficulty difficulty)
{
    m_playerTiles.Init(domino, difficulty);

	std::cout << "Player add tiles!" << std::endl;
}

void Player::RemoveTile(int idx)
{
    m_playerTiles.Remove(idx);
}

void Player::HideTile(int idx)
{
    m_playerTiles.Hide(idx);
}

void Player::ResetPlayedTiles()
{
    m_playerTiles.ResetPlayed();
}

void Player::ClearPlayerTiles()
{
    m_playerTiles.ClearPlayer();
}

void Player::RotateTile(int idx)
{
    //m_playerTiles[idx].Rotate();
}

int Player::GetPlayedTiles() const
{
    return m_playerTiles.GetPlayed();
}

int Player::GetPlayerTilesSize() const
{
    return m_playerTiles.GetSize();
}

Tile& Player::GetTile(int idx)
{
    return m_playerTiles.GetCurrent(idx);
}

void Player::SetStartValue(Vector2D values)
{
    m_startValues.x = values.x;
    m_startValues.y = values.y;
}

void Player::BackToStartValue(int idx)
{
    m_playerTiles.Show(idx, std::to_string(m_startValues.x), std::to_string(m_startValues.y));
}

bool Player::HandleTile(Vector2D posDown, Vector2D posUp, Table* m_table)
{
    for(int i = 0; i < GetPlayerTilesSize(); ++i)
    {
        if(ClickTile(posDown, posUp, GetCurrentTilePos(i), GetTileWidth(), GetTileHeight()))
        {
            UnselectAllTiles();
            SelectCurrentTile(i);
            std::cout << "Player tile is clicked " << i << " " << GetTile(i).GetFirst() << "-"
                      << GetTile(i).GetSecond() << std::endl;
            SetStartValue(Vector2D{ std::stoi(GetTile(i).GetFirst()), std::stoi(GetTile(i).GetSecond()) });
            // m_table->HideOldAvailablePieces();
            // m_table->ShowAvailablePieces(GetTile(i).GetFirst(), GetTile(i).GetSecond());

            return true;
        }
    }

    return false;
}

void Player::AddWin()
{
    m_win++;
}

void Player::ResetWin()
{
    m_win = 0;
}

int Player::GetWin() const
{
    return m_win;
}

Vector2D Player::GetCurrentTilePos(int idx) const
{
    return Vector2D(m_playerTiles.GetCurrentPos(idx));
}

bool Player::AddTileToTable(Vector2D posDown, Vector2D posUp, Table *m_table)
{
    if(!IsPossibleToAddCurrentTile() && ClickInMatrix(posDown, posUp))
    {
        for(int i = 0; i < GetPlayerTilesSize(); ++i)
        {
            if(GetTile(i).IsSelected())
            {
                SetIsPossibleToAddCurrentTile(m_table->CheckForPlacement(GetTile(i), posDown, posUp));
                if(IsPossibleToAddCurrentTile())
                {
                    RemoveTile(i);
                    SetIsPossibleToAddCurrentTile(false);

                    return true;
                }
                else {
                    std::cout << "This tile not possible to add!" << std::endl;
                }
            }
        }
    }

    return false;
}

bool Player::ClickTile(Vector2D posDown, Vector2D posUp, Vector2D currentTilePos, int tileWidth, int tileHeight) const
{
    if((posDown.x > currentTilePos.x && posDown.x < (currentTilePos.x + tileWidth)) && (posUp.x > currentTilePos.x && posUp.x < (currentTilePos.x + tileWidth)) &&
        (posDown.y > currentTilePos.y && posDown.y < (currentTilePos.y + tileHeight)) && (posUp.y > currentTilePos.y && posUp.y < (currentTilePos.y + tileHeight)))
    {
        return true;
    }

    return false;
}

bool Player::ClickInMatrix(Vector2D posDown, Vector2D posUp) const
{
    if((posDown.x > GetMatrixX() && posDown.x < (GetMatrixX() + GetMatrixPieceSize() * (GetMatrixPiecesInRow()))) &&
        (posUp.x > GetMatrixX() && posUp.x < (GetMatrixX() + GetMatrixPieceSize() * (GetMatrixPiecesInRow()))) &&
        (posDown.y > GetMatrixY() && posDown.y < (GetMatrixY() + GetMatrixPieceSize() * GetMatrixPiecesInRow())) &&
        (posUp.y > GetMatrixY() && posUp.y < (GetMatrixY() + GetMatrixPieceSize() * GetMatrixPiecesInRow())))
    {
        std::cout << "Player click in matrix" << std::endl;

        return true;
    }

    return false;
}

std::string Player::WritePlayerData() const
{
    std::string data = m_playerTiles.WritePlayerTiles();
    data += std::to_string(m_win) + " ";

    data += "\n";

    return data;
}

void Player::SetPlayerData(SDL_Renderer* ren, std::vector<std::string> playerData, ClassicTileType type, std::string domino)
{
    m_win = stoi(playerData.back());
    playerData.pop_back();
    m_playerTiles.SetPlayerTilesData(ren, playerData, type, domino);
}

void Player::SetIsPossibleToAddCurrentTile(bool state)
{
    m_playerTiles.SetIsPossibleToAddCurrent(state);
}

bool Player::IsPossibleToAddCurrentTile() const
{
    return m_playerTiles.IsPossibleToAddCurrent();
}

void Player::UnselectAllTiles()
{
    m_playerTiles.UnselectAll();
}

void Player::SelectCurrentTile(int idx)
{
    m_playerTiles.SelectCurrent(idx);
}

void Player::Render()
{
    m_playerTiles.Render();
}
