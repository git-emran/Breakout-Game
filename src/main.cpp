#include "raylib.h"
#include <cstdlib>
#include <string>
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

  // Image data
  Image imgBackground = LoadImage("assets/background.png");
  texBackground = LoadTextureFromImage(imgBackground);
  UnloadImage(imgBackground);

  // loading the paddle data
  player.rect = Rectangle{250.0f, 540.0f, player.w, player.h};
  player.score = 0;

  // ball data
  ball.pos = Vector2{300, 300};
  ball.velocity = 300.0f;

  std::vector<Color> COLORS{RED,     ORANGE, BROWN,   PURPLE,
                            MAGENTA, PINK,   DARKGRAY};

  Brick newBrick;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      newBrick.rect = Rectangle{float(40 + (i * 55)), float(50 + (j * 26)),
                                newBrick.w, newBrick.h

      };

      newBrick.color = COLORS[rand() % COLORS.size()];
      bricks.push_back(newBrick);
    }
  }
}

void GameUpdate() {
  float frameTime = GetFrameTime();

  if (IsKeyDown(KEY_LEFT)) {
    player.rect.x = player.rect.x - (player.velocity * frameTime);
  }

  if (IsKeyDown(KEY_RIGHT)) {
    player.rect.x = player.rect.x + (player.velocity * frameTime);
  }

  ball.pos.x = ball.pos.x + ((ball.velocity * ball.acceleration.x) * frameTime);
  ball.pos.y = ball.pos.y + ((ball.velocity * ball.acceleration.y) * frameTime);

  // check collision between each brick and the ball
  Brick brick;
  int random;

  for (int i = 0; i < bricks.size(); i++) {
    brick = bricks[i];
    if (CheckCollisionCircleRec(ball.pos, ball.radius, brick.rect)) {
      ball.acceleration.y = ball.acceleration.y * -1;
      bricks.erase(bricks.begin() + i);
      player.score = player.score + 10;
      random = rand() % 2;
      break;
    }
  }

  // Check collision between walls and ball
  if (ball.pos.x > screenWidth || ball.pos.x < 10) {
    ball.acceleration.x = ball.acceleration.x * -1;
  }

  if (ball.pos.y > screenHeight || ball.pos.y < 10) {
    ball.acceleration.y = ball.acceleration.y * -1;
  }

  // Checking the collision between ball and player
  if (CheckCollisionCircleRec(ball.pos, ball.radius, player.rect)) {
    ball.acceleration.x = ball.acceleration.x * -1;
    ball.acceleration.y = ball.acceleration.y * -1;
  }
}

void GameRender() {
  DrawTexture(texBackground, 0, 0, RAYWHITE);

  // these are the bricks
  Brick brick;
  for (int i = 0; i < bricks.size(); i++) {
    brick = bricks[i];
    DrawRectangle(brick.rect.x, brick.rect.y, brick.rect.width,
                  brick.rect.height, brick.color);
  }

  // Render the ball
  DrawCircle(ball.pos.x, ball.pos.y, ball.radius, RAYWHITE);

  // this is the player aka the yellow bar
  DrawRectangle(player.rect.x, player.rect.y, player.rect.width,
                player.rect.height, YELLOW);

  std::string sScore = std::to_string(player.score);
  std::string temp1 = "SCORE: ";
  std::string temp2 = temp1 + sScore;
  char const *text = temp2.c_str();
  DrawText(text, 10, 10, 30, YELLOW);
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
