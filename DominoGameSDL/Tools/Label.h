#ifndef LABEL_H_
#define LABEL_H_

#include <SDL.h>
#include <string>

class Label
{
public:
    auto GetTexture() const -> SDL_Texture*;
    void SetTexture(SDL_Texture* labelTex);

    auto GetRect()  const -> SDL_Rect;
    auto GetRectX()      const -> int;
    auto GetRectY()      const -> int;
    auto GetRectWidth()  const -> int;
    auto GetRectHeight() const -> int;
    void SetRect(SDL_Rect labelRect);

    auto GetName() const -> std::string;
    void SetName(std::string name);

    void SetVisible(bool state);
    auto IsVisible() const -> bool;

    void Render(SDL_Renderer *renderer) const;

private:
    SDL_Texture* m_labelTex = nullptr;
    SDL_Rect m_labelRect = { 0, 0, 0, 0 };

    std::string m_name;

    bool m_isVisible = false;
};

#endif // LABEL_H_
