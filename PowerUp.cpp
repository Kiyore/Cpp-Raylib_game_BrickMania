#include "PowerUp.h"
#include "Paddle.h"
#include <cstdlib>

// Constructor
PowerUp::PowerUp() 
    : rect1{ 0, 0, 20, 20 }, color(WHITE), type(-1), active(false), fallSpeed(100.0f) {}

void PowerUp::Spawn(int screenWidth) 
{
    rect1.x = GetRandomValue(50, screenWidth - 50); // Random x position
    rect1.y = 0; // Start at the top
    type = GetRandomValue(0, 2); // Random type
    active = true;

    // Assign a color based on type
    switch (type) 
    {
        case 0: color = BLUE; break;  // Expand Paddle
        case 1: color = GREEN; break; // Extra Life
        case 2: color = RED; break;  // Platform Protector
    }
}
void PowerUp::Update(float dt, Paddle& paddle, int& lives, bool& platformProtectorActive) 
{
	Rectangle rectu = paddle.GetRectangle(); 
    if (active) 
    {
    	//active_time += dt;
    	
    	/*if(active_time >= MAX_ACTIVE_TIME)
    	{
    	    active = false;
    	    active_time = 0.0f;
    	    
    	    if(platformProtectorActive)
    	     platformProtectorActive = false;
    	}*/
        rect1.y += fallSpeed * dt;

        Rectangle paddleRect = paddle.GetRectangle(); 
	//Rectangle rectu = paddle.GetRectangle();              
        if (CheckCollisionRecs(rect1, paddleRect)) 
        {
            active = false;
            pactive = true;
            //active_time += dt;
            switch (type) 
            {
                case 0: rectu.width *= 2.0f;
                	 break;  // Expand Paddle
                case 1: lives++; 
                         break;  // Extra Life
                case 2: platformProtectorActive = true; 
                         break;  // Platform Protector
            }
            //paddle.update(rectu);
        }

        // Deactivate if it falls out of bounds
        if (rect1.y > GetScreenHeight()) {
            active = false;
        }
    }
    if(pactive)
    {
    	active_time +=dt;
    	if(active_time >= MAX_ACTIVE_TIME)
    	{
    	    pactive = false;
    	    active_time = 0.0f;
    	    
    	    if(platformProtectorActive)
    	     platformProtectorActive = false;
    	     if(type == 0)
    	     rectu.width = 100;
    	}
    }
         paddle.update(rectu);
} 
void PowerUp::Draw() const 
{
    if (active) 
        DrawRectangleRec(rect1, color);
}

// Check if power-up is active
bool PowerUp::IsActive() const {
    return active;
}

