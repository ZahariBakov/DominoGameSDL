#ifndef RECTANGLE_H_
#define RECTANGLE_H_

struct Rectangle
{
    int x = 0;
    int y = 0;
    int width = 64;
    int height = 32;

    auto operator+(Rectangle other) -> Rectangle;
    auto operator-(Rectangle other) -> Rectangle;
    auto operator*(Rectangle other) -> Rectangle;
    auto operator/(Rectangle other) -> Rectangle;
};

#endif //RECTANGLE_H_
