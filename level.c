#include <ncurses.h>
#include "rogue.h"
#include "level.h"
#include "object.h"
#include "random.h"
#include "room.h"
#include "init.h"
#include "hit.h"

#define swap(x,y) {t = x; x = y; y = t;}

int cur_room;
short party_room = NO_ROOM;
short r_de;

static void make_room(int, int, int, int);
int connect_rooms(int, int);
void fill_out_level(void);
int same_row(int, int);
void put_door(room *, int, int *, int *);
int same_col(int, int);
void draw_simple_passage(int, int, int, int, int);
void fill_it(int, boolean);
boolean mask_room(int, int *, int *, unsigned short);
static void recursive_deadend(int, int *, int, int);

void make_level(void)
{
  int i, j;
  int must_exist1 = 0;
  int must_exist2 = 0;
  int must_exist3 = 0;

  must_exist1 = get_rand(0,5);

  switch (must_exist1) {
    case 0:
      must_exist1 = 0;
      must_exist2 = 1;
      must_exist3 = 2;
      break;
    case 1:
      must_exist1 = 3;
      must_exist2 = 4;
      must_exist3 = 5;
      break;
    case 2:
      must_exist1 = 6;
      must_exist2 = 7;
      must_exist3 = 8;
      break;
    case 3:
      must_exist1 = 0;
      must_exist2 = 3;
      must_exist3 = 6;
      break;
    case 4:
      must_exist1 = 1;
      must_exist2 = 4;
      must_exist3 = 7;
      break;
    case 5:
      must_exist1 = 2;
      must_exist2 = 5;
      must_exist3 = 8;
      break;
  }
  for (i = 0; i < MAXROOMS; i++) {
    make_room(i, must_exist1, must_exist2, must_exist3);
  }
  for (j = 0; j < MAXROOMS; j++) {
    i=j;

    if (i < (MAXROOMS - 1)) {
      connect_rooms(i, i + 1);
    }
    if (i < (MAXROOMS - 3)) {
      connect_rooms(i, i + 3);
    }
    if (i < (MAXROOMS - 2)) {
      if (rooms[i + 1].is_room & R_NOTHING) {
        if (connect_rooms(i, i + 2)) {
          rooms[i+1].is_room = R_CROSS;
        }
      }
    }
    if (i < (MAXROOMS - 6)) {
      if (rooms[i + 3].is_room & R_NOTHING) {
        if (connect_rooms(i, i + 6)) {
          rooms[i + 3].is_room = R_CROSS;
        }
      }
    }
    if (is_all_connected()) {
      break;
    }
    fill_out_level();
  }
}

static void make_room(int rn, int r1, int r2, int r3)
{
  int left_col = 0;
  int right_col = 0;
  int top_row = 0;
  int bottom_row = 0;
  int width, height;
  int row_offset, col_offset;
  int i, j;
  unsigned short ch;

  switch(rn) {
    case 0:
      left_col = 0;
      right_col = COL1 - 1;
      top_row = MIN_ROW;
      bottom_row = ROW1 - 1;
      break;
    case 1:
      left_col = COL1 + 1;
      right_col = COL2 - 1;
      top_row = MIN_ROW;
      bottom_row = ROW1 - 1;
      break;
    case 2:
      left_col = COL2 + 1;
      right_col = DCOLS - 1;
      top_row = MIN_ROW;
      bottom_row = ROW1 - 1;
      break;
    case 3:
      left_col = 0;
      right_col = COL1 - 1;
      top_row = ROW1 + 1;
      bottom_row = ROW2 - 1;
      break;
    case 4:
      left_col = COL1 + 1;
      right_col = COL2 - 1;
      top_row = ROW1 + 1;
      bottom_row = ROW2 - 1;
      break;
    case 5:
      left_col = COL2 + 1;
      right_col = DCOLS - 1;
      top_row = ROW1 + 1;
      bottom_row = ROW2 - 1;
      break;
    case 6:
      left_col = 0;
      right_col = COL1 - 1;
      top_row = ROW2 + 1;
      bottom_row = DROWS - 2;
      break;
    case 7:
      left_col = COL1 + 1;
      right_col = COL2 - 1;
      top_row = ROW2 + 1;
      bottom_row = DROWS - 2;
      break;
    case 8:
      left_col = COL2 + 1;
      right_col = DCOLS - 1;
      top_row = ROW2 + 1;
      bottom_row = DROWS - 2;
      break;
  }
  rooms[rn].is_room = R_ROOM;

  for (i = top_row; i <= bottom_row; i++) {
    for (j = left_col; j <= right_col; j++) {
      if ((i == top_row) || (i == bottom_row)) {
        ch = HORWALL;
      } else {
        if (((i != top_row) && (i != bottom_row)) && ((j == left_col) || (j == right_col))) {
          ch = VERTWALL;
        } else {
          ch = FLOOR;
        }
      }
      dungeon[i][j] = ch;
    }
  }
  rooms[rn].top_row = top_row;
  rooms[rn].bottom_row = bottom_row;
  rooms[rn].left_col = left_col;
  rooms[rn].right_col = right_col;
}

int connect_rooms(int room1, int room2)
{
  int row1, col1, row2, col2, dir;

  if ((!(rooms[room1].is_room & (R_ROOM))) || (!(rooms[room2].is_room & (R_ROOM)))) {
    return 0;
  }
 
  if (same_row(room1, room2) && (rooms[room1].left_col > rooms[room2].right_col)) {
    put_door(&rooms[room1], LEFT, &row1, &col1);
    put_door(&rooms[room2], RIGHT, &row2, &col2);
    dir = LEFT;
  } else {
    if (same_row(room1, room2) && (rooms[room2].left_col > rooms[room1].right_col)) {
      put_door(&rooms[room1], RIGHT, &row1, &col1);
      put_door(&rooms[room2], LEFT, &row2, &col2);
      dir = RIGHT;
    } else {
      if (same_col(room1, room2) && (rooms[room1].top_row > rooms[room2].bottom_row)) {
        put_door(&rooms[room1], UP, &row1, &col1);
        put_door(&rooms[room2], DOWN, &row2, &col2);
        dir = UP;
      } else {
        if (same_col(room1, room2) && (rooms[room2].top_row > rooms[room1].bottom_row)) {
          put_door(&rooms[room1], DOWN, &row1, &col1);
          put_door(&rooms[room2], UP, &row2, &col2);
          dir = DOWN;
        } else {
          return 0;
        }
      }
    }
  }

  do {
    draw_simple_passage(row1, col1, row2, col2, dir);
  } while (rand_percent(4));

  rooms[room1].doors[dir / 2].oth_room = room2;
  rooms[room1].doors[dir / 2].oth_row = row2;
  rooms[room1].doors[dir / 2].oth_col = col2;

  rooms[room2].doors[(((dir + 4) % DIRS) / 2)].oth_room = room1;
  rooms[room2].doors[(((dir + 4) % DIRS) / 2)].oth_row = row1;
  rooms[room2].doors[(((dir + 4) % DIRS) / 2)].oth_col = col1;

  return 1;
}

void clear_level(void)
{
  for (unsigned int i=0;i<MAXROOMS;i++) {
    rooms[i].is_room = R_NOTHING;
    for (unsigned int j = 0; j < MAXDOORS; j++) {
      rooms[i].doors[j].oth_room = NO_ROOM;
    }
  }

  for (unsigned int i = 0; i < DROWS; i++) {
    for (unsigned int j = 0; j < DCOLS; j++) {
      dungeon[i][j] = NOTHING;
    }
  }
  party_room = NO_ROOM;
  rogue.row=-1;
  rogue.col=-1;
  clear();
}

void put_door(room *rm, int dir, int *row, int *col)
{
  switch (dir) {
    case UP:
    case DOWN:
      *row = ((dir == UP) ? rm->top_row : rm->bottom_row);
      do {
        *col = get_rand(rm->left_col + 1,rm->right_col - 1);
      } while (!(dungeon[*row][*col] & (HORWALL | TUNNEL)));
      break;
    case RIGHT:
    case LEFT:
      *col = (dir == LEFT) ? rm->left_col : rm->right_col;
      do {
        *row = get_rand(rm->top_row + 1,rm->bottom_row - 1);
      } while (!(dungeon[*row][*col] & (VERTWALL | TUNNEL)));
      break;
  }
  if (rm->is_room & R_ROOM) {
    dungeon[*row][*col] = DOOR;
  }
  rm->doors[dir / 2].door_row = *row;
  rm->doors[dir / 2].door_col = *col;
}

void draw_simple_passage(int row1, int col1, int row2, int col2, int dir)
{
  int i;
  int middle;
  int t;

  if ((dir == LEFT) || (dir == RIGHT)) {
    if (col1 > col2) {
      swap(row1, row2);
      swap(col1, col2);
    }
    middle = get_rand(col1 + 1, col2 - 1);
    for (i = col1 + 1; i != middle; i++) {
      dungeon[row1][i] = TUNNEL;
    }
    for (i = row1; i != row2; i += (row1 > row2) ? -1 : 1) {
      dungeon[i][middle] = TUNNEL;
    }
    for (i = middle; i != col2; i++) {
      dungeon[row2][i] = TUNNEL;
    }
  } else {
    if (row1 > row2) {
      swap(row1, row2);
      swap(col1, col2);
    }
    middle = get_rand(row1 + 1, row2 - 1);
    for (i = row1 + 1; i != middle; i++) {
      dungeon[i][col1] = TUNNEL;
    }
    for (i = col1; i != col2; i += (col1 > col2) ? -1 : 1) {
      dungeon[middle][i] = TUNNEL;
    }
    for (i = middle; i != row2; i++) {
      dungeon[i][col2] = TUNNEL;
    }
  }
}

int same_row(int room1, int room2)
{
  return((room1 / 3) == (room2 / 3));
}

int same_col(int room1, int room2)
{
  return((room1 % 3) == (room2 % 3));
}

void fill_out_level(void)
{
  r_de = NO_ROOM;

  for (unsigned int i = 0;i<MAXROOMS;i++) {
    int rn=i;
    if ((rooms[rn].is_room & R_NOTHING) || ((rooms[rn].is_room & R_CROSS) && coin_toss())) {
      fill_it(rn, 1);
    }
  }
  if (r_de != NO_ROOM) {
    fill_it(r_de, 0);
  }
}

void fill_it(int rn, boolean do_rec_de)
{
  int i;
  int tunnel_dir;
  int door_dir;
  int drow, dcol;
  int target_room;
  int rooms_found = 0;
  int srow, scol;
  int t;
  static int offsets[4] = {-1, 1, 3, -3};
  boolean did_this = 0;

  for (i = 0; i < 10; i++) {
    srow = get_rand(0, 3);
    scol = get_rand(0, 3);
    t = offsets[srow];
    offsets[srow] = offsets[scol];
    offsets[scol] = t;
  }
  for (i = 0; i < 4; i++) {
    target_room = rn + offsets[i];

    if (((target_room < 0) || (target_room >= MAXROOMS)) || (!(same_row(rn, target_room) || same_col(rn, target_room))) || (!(rooms[target_room].is_room & (R_ROOM /*| R_MAZE*/)))) {
      continue;
    }
    if (same_row(rn, target_room)) {
      tunnel_dir = (rooms[rn].left_col < rooms[target_room].left_col) ? RIGHT : LEFT;
    } else {
      tunnel_dir = (rooms[rn].top_row < rooms[target_room].top_row) ? DOWN : UP;
    }
    door_dir = ((tunnel_dir + 4) % DIRS);
    if (rooms[target_room].doors[door_dir / 2].oth_room != NO_ROOM) {
      continue;
    }
    if (((!do_rec_de) || did_this) || (!mask_room(rn, &srow, &scol, TUNNEL))) {
      srow = (rooms[rn].top_row + rooms[rn].bottom_row) / 2;
      scol = (rooms[rn].left_col + rooms[rn].right_col) / 2;
    }
    put_door(&rooms[target_room], door_dir, &drow, &dcol);
    rooms_found++;
    draw_simple_passage(srow, scol, drow, dcol, tunnel_dir);
    rooms[rn].is_room = R_DEADEND;
    dungeon[srow][scol] = TUNNEL;

    if ((i < 3) && (!did_this)) {
      did_this = 1;
      if (coin_toss()) {
        continue;
      }
    }
    if ((rooms_found < 2) && do_rec_de) {
      recursive_deadend(rn, offsets, srow, scol);
    }
    break;
  }
}

static void recursive_deadend(int rn, int *offsets, int srow, int scol)
{
  int i;
  int de;
  int drow, dcol;
  int tunnel_dir;

  rooms[rn].is_room = R_DEADEND;
  dungeon[srow][scol] = TUNNEL;

  for (i = 0; i < 4; i++) {
    de = rn + offsets[i];
    if (((de < 0) || (de >= MAXROOMS)) || (!(same_row(rn, de) || same_col(rn, de)))) {
      continue;
    }
    if (!(rooms[de].is_room & R_NOTHING)) {
      continue;
    }
    drow = (rooms[de].top_row + rooms[de].bottom_row) / 2;
    dcol = (rooms[de].left_col + rooms[de].right_col) / 2;
    if (same_row(rn, de)) {
      tunnel_dir = (rooms[rn].left_col < rooms[de].left_col) ? RIGHT : LEFT;
    } else {
      tunnel_dir = (rooms[rn].top_row < rooms[de].top_row) ? DOWN : UP;
    }
    draw_simple_passage(srow, scol, drow, dcol, tunnel_dir);
    r_de = de;
    recursive_deadend(de, offsets, drow, dcol);
  }
}

boolean mask_room(int rn, int *row, int *col, unsigned short mask)
{
  int i, j;

  for (i = rooms[rn].top_row; i <= rooms[rn].bottom_row; i++) {
    for (j = rooms[rn].left_col; j <= rooms[rn].right_col; j++) {
      if (dungeon[i][j] & mask) {
        *row = i;
        *col = j;
        return 1;
      }
    }
  }
  return 0;
}

void put_player(int nr)
{
  int rn = nr;
  int misses;
  int row, col;

  for (misses = 0; ((misses < 2) && (rn == nr)); misses++) {
    gr_row_col(&row, &col, (FLOOR | TUNNEL /*| OBJECT | STAIRS*/));
    rn = get_room_number(row, col);
  }
  rogue.row = row;
  rogue.col = col;

  if (dungeon[rogue.row][rogue.col] & TUNNEL) {
    cur_room = PASSAGE;
  } else {
    cur_room = rn;
  }
  if (cur_room != PASSAGE) {
    light_up_room(cur_room);
  } else {
    light_passage(rogue.row, rogue.col);
  }
  mvaddch(rogue.row, rogue.col, rogue.fchar);
}
