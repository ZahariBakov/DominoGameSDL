#include "Rectangle.h"

Rectangle Rectangle::operator+(Rectangle other)
{
    Rectangle temp;
    temp.x = this->x + other.x;
    temp.y = this->y + other.y;

    return temp;
}

Rectangle Rectangle::operator-(Rectangle other)
{
    Rectangle temp;
    temp.x = this->x - other.x;
    temp.y = this->y - other.y;

    return temp;
}

Rectangle Rectangle::operator*(Rectangle other)
{
    Rectangle temp;
    temp.x = this->x * other.x;
    temp.y = this->y * other.y;

    return temp;
}

Rectangle Rectangle::operator/(Rectangle other)
{
    Rectangle temp;
    temp.x = this->x / other.x;
    temp.y = this->y / other.y;

    return temp;
}
