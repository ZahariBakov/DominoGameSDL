#pragma once

#include "Tile.h"
#include "Tools/Vector2D.h"

#include<string>
#include <vector>

class Table
{
public:
	Table();

    // - Add tile at the center of the table
    void Init(Tile tile);

    void ShowAvailablePieces(); 

    auto CheckForPlacement(Tile playerTile, Vector2D posDown, Vector2D posUp) -> bool;

    void CreateMap();

    void Render() const;
    void SetRenderer(SDL_Renderer* renderer);
    void Clear();

    auto WriteTableData() const -> std::string;
    void SetTableData(std::vector<std::string> tableData);

private:
    void AddTile(Tile newTile, Vector2D tilePos);

    void ShowAvailableFirstFreePieces();
    void ShowAvailableSecondPieces();
    void HideOldAvailablePieces();

    struct CheckTileData
    {
        CheckTileData( const Tile& playerTile, const Box& firstBox, const Box& secondBox, const Box& thirdBox,
                      const Vector2D& firstBoxPos, const Vector2D& secondBoxPos, const Vector2D& thirdBoxPos)
            : playerTile(playerTile), firstBox(firstBox), secondBox(secondBox), thirdBox(thirdBox),
            firstBoxPos(firstBoxPos), secondBoxPos(secondBoxPos), thirdBoxPos(thirdBoxPos)
        {

        }

        const Tile& playerTile;
        const Box& firstBox;
        const Box& secondBox;
        const Box& thirdBox;
        const Vector2D& firstBoxPos;
        const Vector2D& secondBoxPos;
        const Vector2D& thirdBoxPos;
    };

    //TODO - use const & if used as read only
    auto CheckTileFirstWithFirstFree(CheckTileData) const -> bool;
    auto CheckTileFirstWithSecondFree(CheckTileData) const -> bool;
    auto CheckTileSecondWithFirstFree(CheckTileData) const -> bool;
    auto CheckTileSecondWithSecondFree(CheckTileData) const -> bool;

    void SecondTileMatchWithFirstFree(Tile playerTile, int xPress, int yPress);
    void SecondTileMatchWithSecondFree(Tile playerTile, int xPress, int yPress);

    //Add tableBox size as const variable.
    static const int TABLE_SIZE = 20;

    Box m_tableBox[TABLE_SIZE][TABLE_SIZE]{};
    // Tile m_tableTile[TABLE_SIZE][TABLE_SIZE / 2];

    std::string m_firstFreeValue;
    std::string m_secondFreeValue;

    Vector2D m_firstFreePos;
    Vector2D m_secondFreePos;

    SDL_Renderer* m_renderer;
};
