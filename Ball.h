#ifndef BALL_H
#define BALL_H

#include <raylib.h>

class Ball 
{
public:
    Ball(float x, float y, float radius);
    void Update(float& speedX, float& speedY, Rectangle paddle, int& lives, bool& gameOver,int &flag,float spd,int diff,bool ppa);
    void Draw() const;
    Vector2 GetPosition() const;

private:
    Vector2 position;
    float radius;
};

#endif // BALL_H
