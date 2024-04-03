#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include "Tools/Vector2D.h"

auto GetWindowsWidth() -> int;
auto GetWindowHeight() -> int;

auto GetMatrixX() -> int;
auto GetMatrixY() -> int;

auto GetMatrixPieceSize() -> int;
auto GetMatrixPiecesInRow() -> int;
auto GetPenultimateMatrixPiece() -> int;

auto GetTileWidth() -> int;
auto GetTileHeight() -> int;

auto GetTableX() -> int;
auto GetTableY() -> int;
auto GetCenterTablePos() -> Vector2D;

auto GetPlayerMaxWinCount() -> int;

#endif // GAMECONSTANTS_H
