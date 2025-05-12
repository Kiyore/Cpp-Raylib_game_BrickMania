#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, bool exists, bool isBreakable)
    : rect{ x, y, width, height }, active(exists), breakable(isBreakable) {by = y; bh = height;}

void Brick::Draw() const 
{
    if (active) 
    {
        if (breakable) {
            DrawRectangleRec(rect, RED); // Breakable bricks in red
        } else {
            DrawRectangleRec(rect, GRAY); // Non-breakable bricks in gray
        }
    }
}

int Brick::CheckCollision(Vector2 ballPos, int radius) 
{
   if (IsActive()) 
        {
            if((CheckCollisionCircleRec(ballPos, radius, rect) && ballPos.y > (by+bh))	||   (CheckCollisionCircleRec(ballPos, radius, rect) && ballPos.y < by))
            	return 1;
            else if((CheckCollisionCircleRec(ballPos, radius, rect)))
            return 2; 
        }
        return 0;
}

void Brick::Destroy() {
    if (breakable) {
        active = false; // Only destroy breakable bricks
    }
}

bool Brick::IsActive() const { return active; }
bool Brick::IsBreakable() const { return breakable; }
