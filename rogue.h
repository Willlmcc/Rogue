#ifndef _ROGUE_H_
#define _ROGUE_H_

#define boolean char

#define NOTHING		((unsigned short)     0)
#define HORWALL		((unsigned short)   010)
#define VERTWALL	((unsigned short)   020)
#define DOOR		((unsigned short)   040)
#define FLOOR		((unsigned short)  0100)
#define TUNNEL		((unsigned short)  0200)
#define HIDDEN		((unsigned short) 01000)

#define MAX_PACK_COUNT 24

#define DROWS 24
#define DCOLS 80
#define MORE " -- More --"

#define INIT_HP 12

struct fight
{
  short row, col;
  short fchar;
};

typedef struct fight fighter;

#define MAXROOMS 9

#define MAXDOORS 4

#define NO_ROOM -1

#define PASSAGE -3		/* cur_room value */

enum room_type
{
  R_NOTHING = 01,
  R_ROOM = 02,
  R_MAZE = 04,
  R_DEADEND = 010,
  R_CROSS = 020
};

#define LAST_DUNGEON 99

#define UP 0
#define UPRIGHT 1
#define RIGHT 2
#define RIGHTDOWN 3
#define DOWN 4
#define DOWNLEFT 5
#define LEFT 6
#define LEFTUP 7
#define DIRS 8

#define ROW1 7
#define ROW2 15

#define COL1 26
#define COL2 52

#define MOVED 0
#define MOVE_FAILED -1
#define STOPPED_ON_SOMETHING -2

#define MIN_ROW 1

#endif
