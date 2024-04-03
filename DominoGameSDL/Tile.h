#pragma once

#include<string>
#include "Box.h"
#include "Tools/Vector2D.h"

class Tile
{
public:
    Tile(){};
    Tile(SDL_Renderer* ren, std::string first, std::string second, ClassicTileType type, std::string domino);

    auto GetFirst() const -> std::string;
    auto GetSecond() const -> std::string;

    auto GetPos() const -> Vector2D;
    void SetPosition(Vector2D tilePos);
    void SetVertical(Vector2D tilePos);
    void SetHorizontal(Vector2D tilePos);

    auto IsSelected() const -> bool;
    void SetIsSelected(bool state);

    void Render();
    void Swap();
    void UpRotate();
    void DownRotate();

    void SetValues(std::string first, std::string second);
    void RemoveValues();

    void SetVisible(bool state);
    auto IsVisible() const -> bool;

    auto IsHorizontal() const -> bool;

private:
    bool m_isHorizontal = true;

    Box m_first;
    Box m_second;

    bool m_isVisible = true;
    bool m_isSelected = false;
};
