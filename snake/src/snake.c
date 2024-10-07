// #include <stdlib.h>
#include "snake.h"

// Is it in snakes body
int in_body(Snake *snake, Coordinate object) {
  int hit = 0;
  for (int i = 1; i < snake->length; i++) {
    if (snake->coordinates[i].x == object.x &&
        snake->coordinates[i].y == object.y) {

      hit = 1;
    }
  }
  return hit;
}

// Finds distance from head to own body
float find_nearest(Snake *snake, int dir) {
  Coordinate head = snake->coordinates[0];
  if (dir == 0) {
    for (int i = head.y; i >= 0; i--) {
      Coordinate temp = {head.x, i};
      if (in_body(snake, temp)) {
        return head.y - i;
      }
    }
    return 100;
  } else if (dir == 1) {
    for (int i = head.x; i < 8; i++) {
      Coordinate temp = {i, head.y};
      if (in_body(snake, temp)) {
        return i - head.x;
      }
    }
    return 100;
  } else if (dir == 2) {
    for (int i = head.y; i < 8; i++) {
      Coordinate temp = {head.x, i};
      if (in_body(snake, temp)) {
        return i - head.y;
      }
    }
    return 100;
  } else {
    for (int i = head.x; i >= 0; i--) {
      Coordinate temp = {i, head.y};
      if (in_body(snake, temp)) {
        return head.x - i;
      }
    }
    return 100;
  }
}

// State for neural network input. Distances snake sees
void get_state(int (*state)[], Snake *snake, Coordinate *food) {
  int x = snake->coordinates[0].x;
  int y = snake->coordinates[0].y;
  // Distance to edges
  (*state)[0] = (int)y;
  (*state)[1] = 7 - x;
  (*state)[2] = 7 - y;
  (*state)[3] = x;
  // Distance to food
  (*state)[4] = y - food->y >= 0 ? y - food->y : 100;
  (*state)[5] = food->x - x >= 0 ? food->x - x : 100;
  (*state)[6] = food->y - y >= 0 ? food->y - y : 100;
  (*state)[7] = x - food->x >= 0 ? x - food->x : 100;
  // Distance to own body
  (*state)[8] = find_nearest(snake, 0);
  (*state)[9] = find_nearest(snake, 1);
  (*state)[10] = find_nearest(snake, 2);
  (*state)[11] = find_nearest(snake, 3);
}

// Initializes snake into starting state
void init_snake(Snake *snake, Coordinate *food, int (*state)[]) {

  snake->coordinates[0].x = 2;
  snake->coordinates[0].y = 5;
  snake->coordinates[1].x = 2;
  snake->coordinates[1].y = 4;
  snake->coordinates[2].x = 2;
  snake->coordinates[2].y = 3;
  snake->length = 3;
  snake->action = 3;
  snake->prev_action = 3;
  food->x = 3;
  food->y = 3;
  get_state(state, snake, food);
}

void add_front(Snake *snake, Coordinate piece) {

  for (int i = snake->length - 1; i >= 0; i--) {
    snake->coordinates[i + 1].x = snake->coordinates[i].x;
    snake->coordinates[i + 1].y = snake->coordinates[i].y;
  }
  snake->coordinates[0].x = piece.x;
  snake->coordinates[0].y = piece.y;
  snake->length = snake->length + 1;
}

int move(Snake *snake, Coordinate *food, int (*state)[]) {

  int end = 0;

  // Can't turn 180 degrees
  if ((snake->action == 0 && snake->prev_action == 1) ||
      (snake->action == 1 && snake->prev_action == 0) ||
      (snake->action == 2 && snake->prev_action == 3) ||
      (snake->action == 3 && snake->prev_action == 2)) {
    snake->action = snake->prev_action;
  }
  if (snake->action == 0) { // down
    Coordinate temp = {snake->coordinates[0].x, snake->coordinates[0].y + 1};
    add_front(snake, temp);

  } else if (snake->action == 1) { // up
    Coordinate temp = {snake->coordinates[0].x, snake->coordinates[0].y - 1};
    add_front(snake, temp);

  } else if (snake->action == 2) { // left
    Coordinate temp = {snake->coordinates[0].x - 1, snake->coordinates[0].y};
    add_front(snake, temp);

  } else { // right
    Coordinate temp = {snake->coordinates[0].x + 1, snake->coordinates[0].y};
    add_front(snake, temp);
  }

  // Ending conditions. Hitting the walls or own body
  if (snake->coordinates[0].x < 0 || snake->coordinates[0].y < 0 || snake->coordinates[0].x > 7 || snake->coordinates[0].y > 7 /*||
			!in_body(snake, snake->coordinates[0])*/){

    end = 1;
  } else {
    if (snake->coordinates[0].x == food->x &&
        snake->coordinates[0].y == food->y) {
      food->x = rand() % 8;
      food->y = rand() % 8;
      while (in_body(snake, *food)) {
        food->x = rand() % 8;
        food->y = rand() % 8;
      }

    } else {
      snake->length = snake->length - 1;
    }
  }

  get_state(state, snake, food);

  return end;
}
