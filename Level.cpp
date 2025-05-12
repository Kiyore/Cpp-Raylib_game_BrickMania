#include "Level.h"
#include <raylib.h>
#include "Brick.h"
#include <algorithm>

void Level::InitializeLevel(int level, int brickMatrix[ROWS][COLS]) 
{
    for (int row = 0; row < ROWS; ++row) 
    {
        for (int col = 0; col < COLS; ++col) 
            brickMatrix[row][col] = 0; 
    }

    if (level == 1) 
    {
        int level1[ROWS][COLS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 1, 0},
            {1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
        };
        std::copy(&level1[0][0], &level1[0][0] + ROWS * COLS, &brickMatrix[0][0]);
    } 
    else if (level == 2) 
    {
        int level2[ROWS][COLS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 1, 0}
        };
        std::copy(&level2[0][0], &level2[0][0] + ROWS * COLS, &brickMatrix[0][0]);
    } 
    else if (level == 3) 
    {
        int level3[ROWS][COLS] = {
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {2, 1, 0, 0, 0, 0, 0, 0, 1, 2},
            {2, 1, 0, 2, 2, 2, 2, 0, 1, 2},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };
        std::copy(&level3[0][0], &level3[0][0] + ROWS * COLS, &brickMatrix[0][0]);
    }
    else if(level > 3)
    {
        for (int row = 0; row < ROWS; ++row) 
        {
            for (int col = 0; col < COLS; ++col)
                brickMatrix[row][col] = GetRandomValue(0, 2); // 0: empty, 1: breakable, 2: non-breakable
        }
    }
}

bool Level::AreAllBreakableBricksDestroyed(const std::vector<Brick>& bricks) 
{
    for (const auto& brick : bricks) 
    {
        if (brick.IsBreakable() && brick.IsActive()) 
            return false;
    }
    return true;
}
