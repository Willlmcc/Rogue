#include <ncurses.h>
#include <ctype.h>
#include "rogue.h"
#include "hit.h"
#include "keys.h"
#include "level.h"
#include "message.h"
#include "move.h"
#include "object.h"
#include "play.h"
#include "room.h"
#include "init.h"

boolean interrupted = 0;
char *unknown_command = "Unknown command.";

void play_level(void)
{
  short ch;
  int count;

  for (;;) {
    interrupted = 0;
    move(rogue.row, rogue.col);
    refresh();

    ch = rgetchar();
    count = 0;
CH:
    switch (ch) {
      case ROGUE_KEY_NORTH:
      case ROGUE_KEY_SOUTH:
      case ROGUE_KEY_EAST:
      case ROGUE_KEY_WEST:
      case ROGUE_KEY_NORTHEAST:
      case ROGUE_KEY_NORTHWEST:
      case ROGUE_KEY_SOUTHEAST:
      case ROGUE_KEY_SOUTHWEST:
        one_move_rogue(ch, 1);
        break;
        break;
		case ROGUE_KEY_QUIT:
			clean_up("");
			break;
		case ROGUE_KEY_NOP:
			break;
		default:
			break;
		}
	}
}
