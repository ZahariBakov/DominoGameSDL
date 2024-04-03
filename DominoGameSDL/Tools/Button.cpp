#include "Button.h"
#include "../TextureManager.h"

Button::Button(SDL_Texture *btnTex, SDL_Rect btnRect, std::string name)
{
    m_btnLabel.SetTexture(btnTex);

    m_btnLabel.SetRect(btnRect);

    m_buttonSize.y = m_btnLabel.GetRectHeight();
    m_buttonSize.x = m_btnLabel.GetRectWidth();
    m_buttonPos.x = m_btnLabel.GetRectX();
    m_buttonPos.y = m_btnLabel.GetRectY();

    m_btnLabel.SetName(name);
    m_name = name;
}

SDL_Texture* Button::GetTexture() const
{
    return m_btnLabel.GetTexture();
}

SDL_Rect Button::GetRect() const
{
    return m_btnLabel.GetRect();
}

std::string Button::GetName() const
{
    return m_name;
}

bool Button::IsVisible() const
{
    return m_isVisible;
}

void Button::SetVisible(bool state)
{
    m_isVisible = state;
}

void Button::Render(SDL_Renderer *renderer) const
{
    if(m_isVisible)
    {
        TextureManager::Instance()->DrawRectangle(renderer, m_buttonPos, m_buttonSize);
        auto rect = GetRect();
        SDL_RenderCopy(renderer, GetTexture(), nullptr, &rect);
    }
}

void Button::HandleEvent(Vector2D posDown, Vector2D posUp)
{
    if(IsPressed(posDown, posUp) && m_isVisible)
    {
        m_isClicked = true;
        m_callback();
    }
}

bool Button::IsPressed(Vector2D posDown, Vector2D posUp)
{
    if(posDown.x < m_buttonPos.x || posDown.y < m_buttonPos.y || posUp.x < m_buttonPos.x || posUp.y < m_buttonPos.y)
    {
        return false;
    }

    if(m_buttonPos.x + m_buttonSize.x < posDown.x || m_buttonPos.x + m_buttonSize.x < posUp.x ||
        m_buttonPos.y + m_buttonSize.y < posDown.y || m_buttonPos.y + m_buttonSize.y < posUp.y)
    {
        return false;
    }

    return true;
}

bool Button::IsClicked() const
{
    return m_isClicked;
}

void Button::Unclick()
{
    m_isClicked = false;
}

void Button::SetCallback(std::function<void()> callback)
{
    m_callback = callback;
}
