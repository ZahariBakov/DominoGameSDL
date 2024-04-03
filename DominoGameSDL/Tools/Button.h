#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <string>
#include <functional>

#include "Vector2D.h"
#include "Label.h"

//TODO - remove btn in function names.
class Button
{
public:
    Button() = default;
    Button(SDL_Texture* btnTex, SDL_Rect btnRect, std::string name);

    auto GetTexture() const -> SDL_Texture*;

    auto GetRect() const -> SDL_Rect;

    auto GetName() const -> std::string;

    void SetVisible(bool state);
    auto IsVisible() const -> bool;

    void Render(SDL_Renderer *renderer) const;

    void HandleEvent(Vector2D posDown, Vector2D posUp);
    auto IsPressed(Vector2D posDown, Vector2D posUp) -> bool;

    auto IsClicked() const -> bool;
    void Unclick();

    void SetCallback(std::function<void()> callback);

private:
    Vector2D m_buttonPos;
    Vector2D m_buttonSize;

    std::string m_name;

    bool m_isVisible = false;
    bool m_isClicked = false;

    Label m_btnLabel;

    std::function<void()> m_callback;
};

#endif // BUTTON_H
