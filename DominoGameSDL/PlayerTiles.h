#ifndef PLAYERTILES_H
#define PLAYERTILES_H

#include <vector>

#include "Domino.h"
#include "Enums.h"
#include "Tools/Vector2D.h"

class PlayerTiles
{
public:
    void Init(Domino& domino, Difficulty difficulty);

    void Remove(int idx);
    void Hide(int idx);
    void Show(int idx, std::string first, std::string second);

    void ResetPlayed();
    auto GetPlayed() const -> int;

    void ClearPlayer();

    auto GetCurrentPos(int idx) const -> Vector2D;

    auto GetCurrent(int idx) -> Tile&;
    auto GetSize() const -> int;

    void SetIsPossibleToAddCurrent(bool state);
    auto IsPossibleToAddCurrent() const -> bool;

    void UnselectAll();
    void SelectCurrent(int idx);

    auto WritePlayerTiles() const -> std::string;
    void SetPlayerTilesData(SDL_Renderer* ren, std::vector<std::string> playerData, ClassicTileType type, std::string domino);

    void Render();

private:
    Vector2D m_playerTilePos{ 1300, 10 };

    int m_playedTile = 0;

    bool m_isPossible = false;

    std::vector<Tile> m_playerTiles;
};

#endif // PLAYERTILES_H
