#include <ncurses.h>
#include "rogue.h"
#include "move.h"
#include "object.h"
#include "random.h"
#include "room.h"
#include "object.h"
#include "hit.h"

room rooms[MAXROOMS];
boolean rooms_visited[MAXROOMS];

void visit_rooms(int);
int get_oth_room(int, int *, int *);

void light_up_room(int rn)
{
  int i, j;

  for (i = rooms[rn].top_row; i <= rooms[rn].bottom_row; i++) {
    for (j = rooms[rn].left_col; j <= rooms[rn].right_col; j++) {
      mvaddch(i, j, get_dungeon_char(i, j));
    }
  }
  mvaddch(rogue.row, rogue.col, rogue.fchar);
}

void light_passage(int row, int col)
{
  short i, j, i_end, j_end;

  i_end = (row < (DROWS-2)) ? 1 : 0;
  j_end = (col < (DCOLS-1)) ? 1 : 0;

  for (i = ((row > MIN_ROW) ? -1 : 0); i <= i_end; i++) {
    for (j = ((col > 0) ? -1 : 0); j <= j_end; j++) {
      if (can_move(row, col, row+i, col+j)) {
        mvaddch(row+i, col+j, get_dungeon_char(row+i, col+j));
      }
    }
  }
}

void darken_room(int rn)
{
  int i, j;

  for (i = rooms[rn].top_row + 1; i < rooms[rn].bottom_row; i++) {
    for (j = rooms[rn].left_col + 1; j < rooms[rn].right_col; j++) {
      if (!(dungeon[i][j])) {
        mvaddch(i, j, ' ');
      }
    }
  }
}

char get_dungeon_char(int row, int col)
{
  unsigned int mask = dungeon[row][col];
  if (mask & (TUNNEL | HORWALL | VERTWALL | FLOOR | DOOR)) {
    if ((mask & (TUNNEL))) {
      return '#';
    }
    if (mask & HORWALL) {
      return('-');
    }
    if (mask & VERTWALL) {
      return('|');
    }
    if (mask & FLOOR) {
      return('.');
    }
    if (mask & DOOR) {
      return('+');
    }
  }
  return(' ');
}

void gr_row_col(int *row, int *col, unsigned short mask)
{
  int rn;
  int r, c;

  do {
    r = get_rand(MIN_ROW, DROWS - 2);
    c = get_rand(0, DCOLS - 1);
    rn = get_room_number(r, c);
  } while ((rn == NO_ROOM) || (!(dungeon[r][c] & mask)) || (dungeon[r][c] & (~mask)) || (!(rooms[rn].is_room & (R_ROOM /* | R_MAZE*/))) || ((r == rogue.row) && (c == rogue.col)));

  *row = r;
  *col = c;
}

short gr_room(void)
{
  int i;

  do {
    i = get_rand(0, MAXROOMS - 1);
  } while (!(rooms[i].is_room & (R_ROOM /*| R_MAZE*/)));

  return i;
}

int get_room_number(int row, int col)
{
  int i;

  for (i = 0; i < MAXROOMS; i++) {
    if ((row >= rooms[i].top_row) && (row <= rooms[i].bottom_row) && (col >= rooms[i].left_col) && (col <= rooms[i].right_col)) {
      return i;
    }
  }
  return NO_ROOM;
}

int is_all_connected(void)
{
  int i;
  int starting_room = 0;

  for (i = 0; i < MAXROOMS; i++) {
    rooms_visited[i] = 0; 
    if (rooms[i].is_room & (R_ROOM /*| R_MAZE*/)) {
      starting_room = i;
    }
  }

  visit_rooms(starting_room);

  for (i = 0; i < MAXROOMS; i++) {
    if ((rooms[i].is_room & (R_ROOM/* | R_MAZE*/)) && (!rooms_visited[i])) {
      return(0);
    }
  }
  return 1;
}

void visit_rooms(int rn)
{
  unsigned int i;
  int oth_rn;

  rooms_visited[rn] = 1;

  for (i=0;i<4;i++) {
    oth_rn = rooms[rn].doors[i].oth_room;
    if ((oth_rn >= 0) && (!rooms_visited[oth_rn])) {
      visit_rooms(oth_rn);
    }
  }
}
