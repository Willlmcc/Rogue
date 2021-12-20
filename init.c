#include <ncurses.h>
#include <stdlib.h>
#include "rogue.h"
#include "init.h"
#include "object.h"
#include "random.h"

void init(void)
{
  initscr();
  if ((LINES < DROWS) || (COLS < DCOLS)) {
    clean_up("Must be played on a 24 x 80 or better screen");
  }
  cbreak();
  noecho();
  nonl();
  get_rand(1,10);
}

void clean_up(char *estr)
{
   endwin();
   exit(0);
}
