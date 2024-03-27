#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int WIDTH = 800;
const int HEIGHT = 450;

typedef struct Circle {
  int id;
  Vector2 position;
  float radius;
  bool isClicked;
  bool active;
  int points;
} Circle;
typedef enum GameScreen { INTRO, GAMEPLAY } GameScreen;

Circle generateCicle(int points) {
  Circle circle;
  circle.radius = 50.0f;
  float x = rand() % (WIDTH - (int)circle.radius * 2 + 1 - (int)circle.radius) +
            (int)circle.radius;
  float y =
      rand() % (HEIGHT - (int)circle.radius * 2 + 1 - (int)circle.radius) +
      (int)circle.radius;
  circle.id = points;
  if (points == 1) {
    circle.active = true;
  } else {
    circle.active = false;
  }
  circle.position.x = x;
  circle.position.y = y;
  circle.isClicked = false;
  circle.points = points * 100;
  return circle;
}

void generateStage(int maxCircles, Circle *circles) {
  for (int i = 0; i < maxCircles; i++) {
    circles[i] = generateCicle(i + 1);
  }
}

void renderStage(int maxCircles, Circle *circles) {
  for (int i = 0; i < maxCircles; i++) {
    if (!circles[i].isClicked && circles[i].active) {
      DrawCircle(circles[i].position.x, circles[i].position.y,
                 circles[i].radius, RED);
      DrawText(TextFormat("%02i", circles[i].points),
               (circles[i].position.x - circles[i].radius / 2),
               (circles[i].position.y - circles[i].radius / 2), 40, BLACK);
    } else if (!circles[i].isClicked) {
      DrawCircle(circles[i].position.x, circles[i].position.y,
                 circles[i].radius, GRAY);
    }
  }
}
void handleClick(Vector2 *mousePoint, int maxCircles, Circle *circles,
                 int *score, Sound *mouseClick) {
  for (int i = 0; i < maxCircles; i++) {
    if (CheckCollisionPointCircle(*mousePoint, circles[i].position,
                                  circles[i].radius) &&
        IsMouseButtonDown(MOUSE_BUTTON_LEFT) && circles[i].active) {
      PlaySound(*mouseClick);
      circles[i].isClicked = true;
      circles[i + 1].active = true;
      *score = (int)circles[i].points;
    }
  }
}
void restartStage(int maxCircles, Circle *circles, int *score) {
  int counter = 0;
  for (int i = 0; i < maxCircles; i++) {
    if (circles[i].isClicked) {
      counter += 1;
    }
  }
  if (counter == maxCircles) {
    memset(circles, 0, sizeof *circles);
    generateStage(maxCircles, circles);
    *score = 0;
  }
}
int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "OSU o theos na to kanei");

  InitAudioDevice();

  Sound mouseClick = LoadSound("../../resources/click.mp3");

  Vector2 mousePoint = {0.0f, 0.0f};

  GameScreen currentScreen = INTRO;

  int score = 0;

  const int maxCircles = 4;
  Circle circles[maxCircles];
  generateStage(maxCircles, circles);

  while (!WindowShouldClose()) {
    mousePoint = GetMousePosition();
    BeginDrawing();
    switch (currentScreen) {
    case INTRO: {
      DrawText("Press Space to start!",
               (WIDTH / 2) - MeasureText("Press Space to start!", 50) / 2,
               HEIGHT / 2, 50, BLACK);
      if (IsKeyPressed(32)) {
        currentScreen = GAMEPLAY;
      }
    } break;
    case GAMEPLAY: {
      DrawText(TextFormat("Score: %02i", score), 20, 20, 40, LIGHTGRAY);
      handleClick(&mousePoint, maxCircles, circles, &score, &mouseClick);
      renderStage(maxCircles, circles);
      restartStage(maxCircles, circles, &score);
    } break;
    default:
      break;
    }

    ClearBackground(RAYWHITE);

    EndDrawing();
  }

  UnloadSound(mouseClick);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}
