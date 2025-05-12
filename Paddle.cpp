#include "Paddle.h"

Paddle::Paddle(float x, float y, float width, float height) {
    rect = { x, y, width, height };
}

void Paddle::Move(float speed) 
{
    if (IsKeyDown(KEY_RIGHT)) 
    {
      rect.x += speed;
      spd = 0.5;
    }
    if (IsKeyDown(KEY_LEFT))
    { 
      rect.x -= speed;
      spd = -0.5;
    }
    // Prevent paddle from moving outside the screen
    if (rect.x < 0)
     rect.x = 0;
    if (rect.x + rect.width > 800) 
     rect.x = 800 - rect.width;
}

Rectangle Paddle::GetRectangle() const {
    return rect;
}

float Paddle::Getspd()
{
	return spd;
}

void Paddle :: update(Rectangle& copy)
{
	rect.width = copy.width;
}
