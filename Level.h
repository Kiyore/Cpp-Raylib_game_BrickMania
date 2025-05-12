#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Brick.h"

#define ROWS 6
#define COLS 10

class Level 
{
public:
    static void InitializeLevel(int level, int brickMatrix[ROWS][COLS]);
    static bool AreAllBreakableBricksDestroyed(const std::vector<Brick>& bricks);
};

#endif

