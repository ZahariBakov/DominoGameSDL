#include "GameConstants.h"

int GetWindowsWidth()
{
    return 1280;
}

int GetWindowHeight()
{
    return 720;
}

int GetMatrixX()
{
    return 300;
}

int GetMatrixY()
{
    return 10;
}

int GetMatrixPieceSize()
{
    return 32;
}

int GetMatrixPiecesInRow()
{
    return 20;
}

int GetPenultimateMatrixPiece()
{
    return GetMatrixPiecesInRow() - 1;
}

int GetTileWidth()
{
    return GetMatrixPieceSize() * 2;
}

int GetTileHeight()
{
    return GetMatrixPieceSize();
}

Vector2D GetCenterTablePos()
{
    int center = GetMatrixPiecesInRow() / 2 - 1;
    return Vector2D(center, center);
}

auto GetPlayerMaxWinCount() -> int
{
    return 9;
}
