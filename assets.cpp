#include "assets.hpp"
#include <curses.h>

namespace settings {
char SNAKECHAR{'o'};
char FRUITCHAR{'#'};
int maxy{0};
int maxx{0};
int inputChar;
bool GAMEOVER{0};
DIRECTIONS CUR_DIR{right};
} // namespace settings

void cursesInit() {
  initscr();
  cbreak();
  curs_set(0);
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
}

void popGameOver() {
  erase();
  mvprintw(settings::maxy / 2, ((settings::maxx / 2) - 9), "GAME_OVER");
  mvprintw(settings::maxy / 2 + 1, ((settings::maxx / 2) - 17),
           "Press any key to exit ...");
  refresh();
}

POS::point_pos(int y, int x) {
  this->y = y;
  this->x = x;
}

void POS::randomPos() {
  this->y = (rand() % (settings::maxy - 10) + 5);
  this->x = (rand() % (settings::maxy - 20) + 10);
}

FRUIT::fruit_information() : character(settings::FRUITCHAR) {
  this->postion.randomPos();
}

FRUIT::fruit_information(int y, int x) : character(settings::FRUITCHAR) ,postion(y, x) {}

void FRUIT::drawFruit() {
  mvprintw(this->postion.y, this->postion.x, "%c", this->character);
}

void FRUIT::checkFruitEaten(vec &body) {
  if ((body[0].second.x == this->postion.x) &&
      (body[0].second.y == this->postion.y)) {
    this->postion.y = (rand() % (settings::maxy - 10) + 5);
    this->postion.x = (rand() % (settings::maxx - 20) + 10);
    body.push_back(
        std::make_pair(settings::SNAKECHAR,
                       POS(body.begin()->second.y, body.begin()->second.x)));
  }
}

void FRUIT::changeFruitPos() {}

void SNAKE::drawSnake() {
  for (auto &t : body) {
    mvprintw(t.second.y, t.second.x, "%c", t.first);
  }
  refresh();
}

void SNAKE::moveToDirection() {

  switch (settings::CUR_DIR) {
  case right:
    body.insert(body.begin(), std::make_pair(settings::SNAKECHAR,
                                             POS(body.begin()->second.y,
                                                 body.begin()->second.x + 1)));
    body.pop_back();
    break;

  case left:
    body.insert(body.begin(), std::make_pair(settings::SNAKECHAR,
                                             POS(body.begin()->second.y,
                                                 body.begin()->second.x - 1)));
    body.pop_back();
    break;

  case up:
    body.insert(body.begin(), std::make_pair(settings::SNAKECHAR,
                                             POS(body.begin()->second.y - 1,
                                                 body.begin()->second.x)));
    body.pop_back();
    break;

  case down:
    body.insert(body.begin(), std::make_pair(settings::SNAKECHAR,
                                             POS(body.begin()->second.y + 1,
                                                 body.begin()->second.x)));
    body.pop_back();
    break;
  }
}

bool SNAKE::collision(POS *head) {
  if (head->x < 0 || head->x >= settings::maxx)
    return true;
  else if (head->y < 0 || head->y >= settings::maxy)
    return true;
  return false;
}

SNAKE::snake_behaviour() {
  using settings::SNAKECHAR;
  for (int i{4}; i >= 0; i--)
    body.push_back(std::make_pair(SNAKECHAR, POS(0, i)));
}
