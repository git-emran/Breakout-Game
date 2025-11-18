#include "raylib.h"

struct Ball {
  Vector2 pos;
  Vector2 acceleration{1.0f, 1.0f};
  float velocity;
  float radius = 5.0f;
};

struct Brick {};
struct Player {};

void GameStartup() {}

void GameUpdate() {}

void GameRender() {}

void GameShutDown() {}

int main() {

  const int screenWidth = 700;
  const int screenHeight = 600;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("RAYYYLIB", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
