#pragma once

#include "Domino.h"
#include "Enums.h"
#include "PlayerTiles.h"
#include "Table.h"
#include "Tools/Vector2D.h"

class Player
{
public:
    /// Tile modification methods
    void AddTiles(Domino& domino, Difficulty difficulty);
    void RemoveTile(int idx);
    void HideTile(int idx);

    void ResetPlayedTiles();
    void ClearPlayerTiles();

    void RotateTile(int idx);

    auto GetPlayedTiles() const -> int;
    auto GetPlayerTilesSize() const -> int;
    auto GetTile(int idx) -> Tile&;
    auto GetCurrentTilePos(int idx) const -> Vector2D;
    auto AddTileToTable(Vector2D posDown, Vector2D posUp, Table* m_table) -> bool;

    auto HandleTile(Vector2D posDown, Vector2D posUp, Table* m_table) -> bool;

    void SetStartValue(Vector2D values);
    void BackToStartValue(int idx);

    void AddWin();
    void ResetWin();
    auto GetWin() const -> int;

    void SetIsPossibleToAddCurrentTile(bool state);
    auto CheckIsPossibleToAddCurrentTile(Tile tile);
    auto IsPossibleToAddCurrentTile() const -> bool;

    void UnselectAllTiles();
    void SelectCurrentTile(int idx);

    auto ClickTile(Vector2D posDown, Vector2D posUp, Vector2D currentTilePos, int tileWidth, int tileHeight) const -> bool;
    auto ClickInMatrix(Vector2D posDown, Vector2D posUp) const -> bool;

    auto WritePlayerData() const -> std::string;
    void SetPlayerData(SDL_Renderer* ren, std::vector<std::string> playerData, ClassicTileType type, std::string domino);

    void Render();

private:
    int m_win = 0;

    bool m_isInMatrix = false;

    PlayerTiles m_playerTiles;

    Vector2D m_startValues;
};
