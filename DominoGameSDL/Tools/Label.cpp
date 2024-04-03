#include "Label.h"

SDL_Texture* Label::GetTexture() const
{
    return m_labelTex;
}

void Label::SetTexture(SDL_Texture *labelTex)
{
    m_labelTex = labelTex;
}

SDL_Rect Label::GetRect() const
{
    return m_labelRect;
}

void Label::SetRect(SDL_Rect labelRect)
{
    m_labelRect = labelRect;
}

std::string Label::GetName() const
{
    return m_name;
}

void Label::SetName(std::string name)
{
    m_name = name;
}

void Label::SetVisible(bool state)
{
    m_isVisible = state;
}

bool Label::IsVisible() const
{
    return m_isVisible;
}

void Label::Render(SDL_Renderer *renderer) const
{
    if(m_isVisible)
    {
        auto rect = GetRect();
        SDL_RenderCopy(renderer, GetTexture(), nullptr, &rect);
    }
}

int Label::GetRectX() const
{
    return m_labelRect.x;
}

int Label::GetRectY() const
{
    return m_labelRect.y;
}

int Label::GetRectWidth() const
{
    return m_labelRect.w;
}

int Label::GetRectHeight() const
{
    return m_labelRect.h;
}
