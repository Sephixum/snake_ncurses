#pragma once

#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>

enum DIRECTIONS { right = 1, left = 2, up = 3, down = 4 };

namespace settings {
extern char SNAKECHAR;
extern char FRUITCHAR;
extern int maxy, maxx;
extern bool GAMEOVER;
extern DIRECTIONS CUR_DIR;
extern int inputChar;
} // namespace settings

void cursesInit();
void popGameOver();

typedef class point_pos {
private:
  int y;
  int x;
  friend class fruit_information;
  friend class snake_behaviour;

public:
  point_pos() = default;
  point_pos(int, int);
  void randomPos();
} POS;

typedef std::vector<std::pair<char, POS>> vec;

typedef class fruit_information {
private:
  POS postion;
  char character;

public:
  fruit_information();
  fruit_information(int, int);
  void drawFruit();
  void checkFruitEaten(vec &);
  void changeFruitPos();
} FRUIT;

typedef class snake_behaviour {
public:
  vec body;
  snake_behaviour();
  void initSnake();
  void drawSnake();
  void moveToDirection();
  bool collision(POS *);
} SNAKE;
