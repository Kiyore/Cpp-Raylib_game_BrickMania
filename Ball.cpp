#include "Ball.h"

Ball::Ball(float x, float y, float radius) : radius(radius) {
    position = { x, y };
}

void Ball::Update(float& speedX, float& speedY, Rectangle paddle, int& lives, bool& gameOver, int &flag,float spd,int diff,bool ppa) 
{
    position.x += speedX;
    position.y += speedY;

    // Ball boundary checks
    if (position.y > GetScreenHeight()) 
    {
    	flag = 0;
        --lives; 
        if (lives == 0) 
            gameOver = true; 
        
         else 
         {
            position = { paddle.x + paddle.width / 2, paddle.y - radius };
            speedX = 0.5;
           speedY = (diff == 1) ? -3.0f : (diff == 2) ? -4.5f : -6.0f;
         }
    }
     else if (position.y - radius < 0) 
        speedY *= -1;

    if (position.x - radius < 0 || position.x + radius > GetScreenWidth()) 
      {
      		speedX *= -1;
      		//speedX -=  0.5;  
      }

    if (CheckCollisionCircleRec(position, radius, paddle)) 
    {
        position.y = paddle.y - radius;     
        position.y = paddle.y - radius;
        speedY *= -1; 
        speedX += spd;
    }
    
     if (ppa && position.y > GetScreenHeight() - 10) {
        position.y = GetScreenHeight() - 10;
        speedY *= -1; // Bounce the ball back upwards
    }
}

void Ball::Draw() const {
    DrawCircleV(position, radius, BLUE);
}

Vector2 Ball::GetPosition() const {
    return position;
}
