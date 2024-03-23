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

void renderStage(Vector2 mousePoint, int maxCircles, Circle *circles) {
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
    if (CheckCollisionPointCircle(mousePoint, circles[i].position,
                                  circles[i].radius) &&
        IsMouseButtonDown(MOUSE_BUTTON_LEFT) && circles[i].active) {

      circles[i].isClicked = true;
      circles[i + 1].active = true;
    }
  }
}

void restartStage(int maxCircles, Circle *circles) {
  int counter = 0;
  for (int i = 0; i < maxCircles; i++) {
    if (circles[i].isClicked) {
      counter += 1;
    }
  }
  if (counter == maxCircles) {
    memset(circles, 0, sizeof *circles);
    generateStage(maxCircles, circles);
  }
}
int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "OSU o theos na to kanei");

  Vector2 mousePoint = {0.0f, 0.0f};

  GameScreen currentScreen = INTRO;
  if (currentScreen == GAMEPLAY) {
    const int maxCircles = 4;
    Circle circles[maxCircles];
    generateStage(maxCircles, circles);
  }
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
      renderStage(mousePoint, maxCircles, circles);
      restartStage(maxCircles, circles);
    } break;
    default:
      break;
    }

    ClearBackground(RAYWHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
