#include <raylib.h>
#include <vector>
#include <fstream>
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "PowerUp.h"
#include "Level.h"

using namespace std;

const float brickWidth = 70.0f;
const float brickHeight = 20.0f;
const float startX = 50.0f;
const float startY = 50.0f;
int high_sc = 0;
int curr_sc = 0;

void Loadhigh() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> high_sc;
        file.close();
    }
}

void Savehigh() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << high_sc;
        file.close();
    }
}

int ShowDifficultyMenu() {
    const Rectangle easyButton = {300, 150, 200, 50};
    const Rectangle mediumButton = {300, 250, 200, 50};
    const Rectangle hardButton = {300, 350, 200, 50};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw buttons
        DrawRectangleRec(easyButton, LIGHTGRAY);
        DrawRectangleRec(mediumButton, LIGHTGRAY);
        DrawRectangleRec(hardButton, LIGHTGRAY);

        DrawText("Select Difficulty", 300, 50, 30, DARKGRAY);
        DrawText("Easy", 370, 165, 20, BLACK);
        DrawText("Medium", 350, 265, 20, BLACK);
        DrawText("Hard", 370, 365, 20, BLACK);

        EndDrawing();

        // Check for mouse clicks on buttons
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();

            if (CheckCollisionPointRec(mouse, easyButton)) return 1;
            if (CheckCollisionPointRec(mouse, mediumButton)) return 2;
            if (CheckCollisionPointRec(mouse, hardButton)) return 3;
        }
    }

    return 1;
}

int main() {
    InitWindow(800, 600, "Brick Matrix Levels with Non-Breakable Bricks");
    SetTargetFPS(60);

    int currentLevel = 1;
    int difficulty = ShowDifficultyMenu();
    Loadhigh();

    // Set ball speed based on difficulty
    float speedX, speedY;
    bool pause = false;
    if (difficulty == 1) 
    {
        speedX = 3.0f;
        speedY = -3.0f;
        currentLevel = 1;
    }
     else if (difficulty == 2) 
     {
        speedX = 4.5f;
        speedY = -4.5f;
        currentLevel = 2;
     } 
     else 
    {
        speedX = 6.0f;
        speedY = -6.0f;
        currentLevel = 3;
    }

    PowerUp powerUp;
    float spawnTimer = 0.0f;
    const float spawnInterval = 30.0f;
    bool ppa = false;
    Paddle paddle(800 / 2 - 50, 580, 100, 10);
    Ball ball(paddle.GetRectangle().x + paddle.GetRectangle().width / 2, paddle.GetRectangle().y - 7, 7);
    int lives = 3;
    bool gameOver = false;
    int flag = 0;

    int brickMatrix[ROWS][COLS];
    Level::InitializeLevel(currentLevel, brickMatrix);

    // Create bricks based on the matrix
    vector<Brick> bricks;
    for (int row = 0; row < ROWS; ++row) 
    {
        for (int col = 0; col < COLS; ++col) 
        {
            if (brickMatrix[row][col] > 0) 
            {
                float x = startX + col * brickWidth;
                float y = startY + row * brickHeight;
                bool isBreakable = (brickMatrix[row][col] == 1);
                bricks.emplace_back(x, y, brickWidth - 5.0f, brickHeight - 5.0f, true, isBreakable);
            }
        }
    }

    while (!WindowShouldClose()) 
    {
        if (IsKeyPressed(KEY_P)) 
         pause = !pause;

        if (!gameOver && !pause) 
        {
            paddle.Move(5.0f);

            if (flag == 0)
                ball = Ball(paddle.GetRectangle().x + paddle.GetRectangle().width / 2, paddle.GetRectangle().y - 7, 7);

            if (IsKeyPressed(KEY_SPACE)) flag = 1;

            if (flag == 1)
                ball.Update(speedX, speedY, paddle.GetRectangle(), lives, gameOver, flag, paddle.Getspd(), difficulty, ppa);

            powerUp.Update(GetFrameTime(), paddle, lives, ppa);
            spawnTimer += GetFrameTime();

            if (spawnTimer >= spawnInterval) 
            {
                spawnTimer = 0.0f;
                if (!powerUp.IsActive())
                    powerUp.Spawn(GetScreenWidth());
            }

            if (ppa)
                DrawRectangle(0, GetScreenHeight() - 10, GetScreenWidth(), 10, BLUE);

            for (auto it = bricks.begin(); it != bricks.end(); ++it) 
           {
    		int k = it->CheckCollision(ball.GetPosition(), 7);
    		if (k == 1) 
    		{
       		 if (it->IsBreakable()) 
       		 {
       		 	it->Destroy();
       		 	bricks.erase(it);
       		 	 curr_sc += 10;
       		 }
        	 speedY *= -1;
        		break;
    		}
    		
    	     else if (k == 2) 
    	     {
        		if (it->IsBreakable())
        		{
        			it->Destroy();
        			bricks.erase(it);
        			 curr_sc += 10;
        		}
	        		speedY *= -1;
        			speedX *= -1;
        			break;	
             }
	  }

            if (Level::AreAllBreakableBricksDestroyed(bricks)) 
            {
                currentLevel++;
                Level::InitializeLevel(currentLevel, brickMatrix);
                bricks.clear();
                for (int row = 0; row < ROWS; ++row) 
                {
                    for (int col = 0; col < COLS; ++col) 
                    {
                        if (brickMatrix[row][col] > 0) 
                        {
                            float x = startX + col * brickWidth;
                            float y = startY + row * brickHeight;
                            bool isBreakable = (brickMatrix[row][col] == 1);
                            bricks.emplace_back(x, y, brickWidth - 5.0f, brickHeight - 5.0f, true, isBreakable);
                        }
                    }
                }
                flag = 0;
            }
        } 
        else 
        {
            if (IsKeyPressed(KEY_R)) 
            {
                lives = 3;
                curr_sc = 0;
                gameOver = false;
                ball = Ball(paddle.GetRectangle().x + paddle.GetRectangle().width / 2, paddle.GetRectangle().y - 7, 7);
                flag = 0;
                speedX = (difficulty == 1) ? 3.0f : (difficulty == 2) ? 4.5f : 6.0f;
                speedY = -speedX;

                bricks.clear();
                Level::InitializeLevel(currentLevel, brickMatrix);
                for (int row = 0; row < ROWS; ++row) 
                {
                    for (int col = 0; col < COLS; ++col) 
                    {
                        if (brickMatrix[row][col] > 0) 
                        {
                            float x = startX + col * brickWidth;
                            float y = startY + row * brickHeight;
                            bool isBreakable = (brickMatrix[row][col] == 1);
                            bricks.emplace_back(x, y, brickWidth - 5.0f, brickHeight - 5.0f, true, isBreakable);
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);

        if (!gameOver) 
        {
          DrawRectangleRec(paddle.GetRectangle(), BLACK);
            ball.Draw();
            for (const auto &brick : bricks)
                brick.Draw();

            powerUp.Draw();

            DrawText(TextFormat("Score: %d", curr_sc), 10, 10, 20, BLACK);
            DrawText(TextFormat("High Score: %d", high_sc), 150, 10, 20, BLACK);
            DrawText(TextFormat("Lives: %d", lives), 700, 10, 20, BLACK);

        } 
        else 
        {
            DrawText("Game Over!", 300, 250, 40, RED);
            DrawText("Press R to Restart", 300, 300, 20, WHITE);
        }
	
	 if (pause) 
	{
   	  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
	    // Draw pause menu text
   	  DrawText("PAUSED", GetScreenWidth()/2 - MeasureText("PAUSED", 40)/2, 200, 40, WHITE);
    	  DrawText("Press P to Resume", GetScreenWidth()/2 - MeasureText("Press P to Resume", 20)/2, 250, 20, WHITE);
    	  DrawText("Press Q to Quit", GetScreenWidth()/2 - MeasureText("Press Q to Quit", 20)/2, 280, 20, WHITE);
	} 
	
        EndDrawing();
    }

    Savehigh();
    CloseWindow();
    return 0;
}

