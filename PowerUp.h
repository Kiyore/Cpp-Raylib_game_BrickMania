#ifndef POWERUP_H
#define POWERUP_H

#include <raylib.h>
#include "Paddle.h"
class PowerUp {
public:
    PowerUp(); // Constructor

    void Spawn(int screenWidth); // Spawn a random power-up
    void Update(float deltaTime, Paddle& paddle, int& lives, bool& platformProtectorActive); // Update power-up
    void Draw() const; // Draw the power-up

    bool IsActive() const; // Check if power-up is active

private:
    Rectangle rect1; // Position and size of the power-up
    Color color; // Color based on type
    int type; // 0: Expand Paddle, 1: Extra Life, 2: Platform Protector
    bool active; // hava ka active check
    bool pactive; // paddle ka active check
    float fallSpeed; 
    float active_time = 0.0f;
    const float MAX_ACTIVE_TIME = 12.0f;
};

#endif // POWERUP_H

