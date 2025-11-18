#include "raylib.h"
#include <vector>

const int screenWidth = 500;
const int screenHeight = 600;

struct Ball {
  Vector2 pos;
  Vector2 acceleration{1.0f, 1.0f};
  float velocity;
  float radius = 5.0f;
};

struct Brick {
  Rectangle rect;
  Color color;
  float w = 50.0f;
  float h = 20.0f;
};

struct Player {
  Rectangle rect;
  float velocity = 250.0f;
  int score = 0;
  float w = 75.0f;
  float h = 10.0f;
};

Texture2D texBackground;
Player player;
Ball ball;

std::vector<Brick> bricks;

void GameStartup() {
  Image imgBackground = LoadImage("assets/background.png");
  texBackground = LoadTextureFromImage(imgBackground);
  UnloadImage(imgBackground);

  player.rect = Rectangle{250.0f, 540.0f, player.w, player.h};
  player.score = 0;
}

void GameUpdate() {
  float frameTime = GetFrameTime();

  if (IsKeyDown(KEY_LEFT)) {
    player.rect.x = player.rect.x - (player.velocity * frameTime);
  }

  if (IsKeyDown(KEY_RIGHT)) {
    player.rect.x = player.rect.x + (player.velocity * frameTime);
  }
}

void GameRender() {
  DrawTexture(texBackground, 0, 0, RAYWHITE);
  Brick brick;

  DrawRectangle(player.rect.x, player.rect.y, player.rect.width,
                player.rect.height, YELLOW);
}

void GameShutDown() {}

int main() {

  InitWindow(screenWidth, screenHeight, "Raylib :: BreakOut");
  SetTargetFPS(60);
  GameStartup();

  while (!WindowShouldClose()) {
    GameUpdate();
    BeginDrawing();
    ClearBackground(BLUE);
    GameRender();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
