#include "Box.h"
#include "TextureManager.h"

Box::Box(SDL_Renderer* renderer, std::string value, ClassicTileType type, std::string domino)
{
    m_value = value;
    m_renderer = renderer;

    std::string typeStr = "white/";
    if(type == ClassicTileType::Black)
    {
        typeStr = "black/";
	}

    std::string path;
    if(domino == "classic/")
    {
		path = "assets/" + domino + typeStr + value + ".png";
	}
    else
    {
		path = "assets/" + domino + value + ".png";
	}
    
    TextureManager::Instance()->LoadTexture(path.c_str(), value, m_renderer);	
}

std::string Box::GetValue() const
{
    return m_value;
}

int Box::GetY() const
{
    return m_boxPos.y;
}

int Box::GetX() const
{
    return m_boxPos.x;
}

Vector2D Box::GetPosition() const
{
    return m_boxPos;
}

void Box::SetPosition(int x, int y)
{
    m_boxPos.x = x;
    m_boxPos.y = y;
}

void Box::SetValue(std::string value)
{
    m_value = value;
}

void Box::Render() const
{
    if(m_value == "*")
    {
		return;
	}
    
    TextureManager::Instance()->DrawTexture(m_value, m_boxPos.x, m_boxPos.y, GetSize(), GetSize(), m_renderer);   
}

void Box::SetRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}

auto Box::GetSize() const -> int
{
    return 32;
}
