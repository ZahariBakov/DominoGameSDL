#include "Vector2D.h"

Vector2D::Vector2D(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator+(Vector2D other)
{
    Vector2D temp;
    temp.x = this->x + other.x;
    temp.y = this->y + other.y;

    return temp;
}

Vector2D Vector2D::operator-(Vector2D other)
{
    Vector2D temp;
    temp.x = this->x - other.x;
    temp.y = this->y - other.y;

    return temp;
}

Vector2D Vector2D::operator*(Vector2D other)
{
    Vector2D temp;
    temp.x = this->x * other.x;
    temp.y = this->y * other.y;

    return temp;
}

Vector2D Vector2D::operator/(Vector2D other)
{
    Vector2D temp;
    temp.x = this->x / other.x;
    temp.y = this->y / other.y;

    return temp;
}

bool Vector2D::operator==(Vector2D other) const
{
    if(x == other.x && y == other.y)
    {
        return true;
    }

    return false;
}
