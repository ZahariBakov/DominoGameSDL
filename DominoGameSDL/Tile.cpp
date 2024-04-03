#include "Tile.h"
#include "Tools/Vector2D.h"

Tile::Tile(SDL_Renderer* ren, std::string first, std::string second, ClassicTileType type, std::string domino)
    : m_first(ren, first, type, domino)
    , m_second(ren, second, type, domino)
{
    m_isSelected = false;
}

std::string Tile::GetFirst() const
{
    return m_first.GetValue();
}

std::string Tile::GetSecond() const
{
    return m_second.GetValue();
}

Vector2D Tile::GetPos() const
{
    return Vector2D(m_first.GetX(), m_first.GetY());
}

void Tile::SetPosition(Vector2D tilePos)
{
    m_first.SetPosition(tilePos.x, tilePos.y);

    if(m_isHorizontal)
    {
        m_second.SetPosition(tilePos.x + m_second.GetSize(), tilePos.y);
    }
    else
    {
        m_second.SetPosition(tilePos.x, tilePos.y + m_second.GetSize());
    }
}

void Tile::SetVertical(Vector2D tilePos)
{
    m_first.SetPosition(tilePos.x, tilePos.y);
    m_second.SetPosition(tilePos.x, tilePos.y + m_second.GetSize());
    m_isHorizontal = false;
}

void Tile::SetHorizontal(Vector2D tilePos)
{
    m_first.SetPosition(tilePos.x, tilePos.y);
    m_second.SetPosition(tilePos.x + m_second.GetSize(), tilePos.y);
    m_isHorizontal = true;
}

bool Tile::IsSelected() const
{
    return m_isSelected;
}

void Tile::Render()
{
    m_first.Render();
    m_second.Render();
}

void Tile::Swap()
{
    std::string newFirst = GetSecond();
    std::string newSecond = GetFirst();
    SetValues(newFirst, newSecond);
}

void Tile::UpRotate()
{
    if(m_isHorizontal)
    {
        SetVertical(Vector2D{ m_first.GetX(), m_first.GetY() });
        Swap();
    }
    else
    {
        SetHorizontal(Vector2D{ m_first.GetX(), m_first.GetY() });
    }
}

void Tile::DownRotate()
{
    if(m_isHorizontal)
    {
        SetVertical(Vector2D{ m_first.GetX(), m_first.GetY() });
    }
    else
    {
        Swap();
        SetHorizontal(Vector2D{ m_first.GetX(), m_first.GetY() });
    }
}

void Tile::SetValues(std::string first, std::string second)
{
    m_first.SetValue(first);
    m_second.SetValue(second);
}

void Tile::RemoveValues()
{
    m_first.SetValue("10");
    m_second.SetValue("10");
}

void Tile::SetVisible(bool state)
{
    m_isVisible = state;
}

bool Tile::IsVisible() const
{
    return m_isVisible;
}

bool Tile::IsHorizontal() const
{
    return m_isHorizontal;
}

void Tile::SetIsSelected(bool state)
{
    m_isSelected = state;
}
