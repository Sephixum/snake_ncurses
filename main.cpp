#include "assets.hpp"

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));

  SNAKE snake;
  FRUIT fruit;

  cursesInit();

  while (!settings::GAMEOVER) {
    getmaxyx(stdscr, settings::maxy, settings::maxx);
    erase();

    fruit.drawFruit();
    snake.drawSnake();

    fruit.checkFruitEaten(snake.body);

    if (snake.collision(&snake.body[0].second)) {
      settings::GAMEOVER = 1;
    }

    settings::inputChar = getch();

    switch (settings::inputChar) {
      using settings::CUR_DIR;
    case 'h':
    case KEY_LEFT:
      if (CUR_DIR != DIRECTIONS::right && CUR_DIR != DIRECTIONS::left)
        CUR_DIR = DIRECTIONS::left;
      break;
    case 'l':
    case KEY_RIGHT:
      if (CUR_DIR != DIRECTIONS::right && CUR_DIR != DIRECTIONS::left)
        CUR_DIR = DIRECTIONS::right;
      break;
    case 'j':
    case KEY_DOWN:
      if (CUR_DIR != DIRECTIONS::down && CUR_DIR != DIRECTIONS::up)
        CUR_DIR = DIRECTIONS::down;
      break;
    case 'k':
    case KEY_UP:
      if (CUR_DIR != DIRECTIONS::down && CUR_DIR != DIRECTIONS::up)
        CUR_DIR = DIRECTIONS::up;
      break;
    case 'q':
      settings::GAMEOVER = 1;
      break;
    }

    snake.moveToDirection();
    delay_output(1000 / 10);
  }
  popGameOver();
  nodelay(stdscr, FALSE);
  getch();
  nocbreak();
  endwin();
  return 0;
}
