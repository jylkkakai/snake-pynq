#ifndef SNAKE
#define SNAKE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t x;
  uint8_t y;
} Coordinate;

typedef struct {
  int length;
  int action;
  int prev_action;
  Coordinate coordinates[65];
} Snake;

float find_nearest(Snake *snake, int dir);
void get_state(int (*state)[], Snake *snake, Coordinate *food);
void init_snake(Snake *snake, Coordinate *food, int (*state)[]);
int move(Snake *snake, Coordinate *food, int (*state)[]);
void add_front(Snake *snake, Coordinate piece);

#endif
