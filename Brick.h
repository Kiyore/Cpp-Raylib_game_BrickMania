#ifndef BRICK_H
#define BRICK_H

#include <raylib.h>

class Brick {
public:
    Brick(float x, float y, float width, float height, bool exists, bool isBreakable);
    void Draw() const;
    int CheckCollision(Vector2 ballPos, int radius);
    void Destroy();
    bool IsActive() const;
    bool IsBreakable() const;

private:
    Rectangle rect;
    int bh;
    int by;
    bool active;
    bool breakable; // True if the brick is breakable
};

#endif // BRICK_H
