#ifndef VECTOR2D_H_
#define VECTOR2D_H_

struct Vector2D
{
    Vector2D() {};
    Vector2D(int x, int y);

    int x = 0;
    int y = 0;

    auto operator+(Vector2D other) -> Vector2D;
    auto operator-(Vector2D other) -> Vector2D;
    auto operator*(Vector2D other) -> Vector2D;
    auto operator/(Vector2D other) -> Vector2D;
    auto operator==(Vector2D other) const -> bool;
};

#endif //VECTOR2D_H_
