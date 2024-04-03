#pragma once

#include <SDL.h>
#include <string>

#include "Tools/Vector2D.h"
#include "Enums.h"

class Box
{
public:
    Box(){};
    Box(SDL_Renderer* renderer, std::string value, ClassicTileType type, std::string domino);

    /// Value related methods
    void SetValue(std::string value);
    auto GetValue() const -> std::string;

    /// Position related methods
    void SetPosition(int x, int y);
    auto GetY() const -> int;
    auto GetX() const -> int;

    auto GetPosition() const -> Vector2D;
    // auto GetSize() const -> Vector2D;

    /// Render related methods
    void SetRenderer(SDL_Renderer* renderer); //Probably not used.
    void Render() const;

    auto GetSize() const -> int;
private:
    std::string m_value = "*";

    Vector2D m_boxPos;

    SDL_Renderer* m_renderer = nullptr;
};
