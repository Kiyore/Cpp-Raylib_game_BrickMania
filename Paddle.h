#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

class Paddle 
{
public:
    Paddle(float x, float y, float width, float height);
    void Move(float speed);
    Rectangle GetRectangle() const;
    float Getspd();
    void update(Rectangle& copy);

private:
    Rectangle rect;
    float spd;
};

#endif // PADDLE_H
