# 🎮 Brick Mania

A fun and simple brick-breaking arcade game where you control a paddle to bounce the ball and smash all the bricks!

## 🛠 Tools Used

* 💻 C++
* 🎨 raylib

## 🚀 How to Run

### 🐧 Linux

1. Install **raylib** on your system.

2. Compile the game:

   ```bash
   g++ Main.cpp Paddle.cpp Ball.cpp Brick.cpp Level.cpp PowerUp.cpp -lraylib -o brick_mania
   ```

3. Run the game:

   ```bash
   ./brick_mania
   ```

### 🪟 Windows

1. Install **raylib** and set it up with your compiler (e.g., MinGW or Visual Studio).

2. Compile the game (MinGW example):

   ```bash
   g++ Main.cpp Paddle.cpp Ball.cpp Brick.cpp Level.cpp PowerUp.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -o brick_mania.exe
   ```

3. Run the game:

   ```bash
   brick_mania.exe
   ```

## ⚠️ Caution

This game was developed in a **Linux environment**. If you encounter any issues compiling or running it on Windows, please notify me!

## 🎮 Controls

* ⬅️ Move Left → Left Arrow
* ➡️ Move Right → Right Arrow
* ❌ Quit → ESC

## ✨ Additional Features

* Add images for paddle, ball, and bricks for a better look
* Add sound effects when the ball hits bricks or walls
* Add background music for more fun gameplay
