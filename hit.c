#include "rogue.h"
#include "hit.h"
#include "keys.h"

void get_dir_rc(short dir, short *row, short *col, short allow_off_screen)
{
  switch(dir) {
    case ROGUE_KEY_WEST:
      if (allow_off_screen || (*col > 0)) {
        (*col)--;
      }
      break;
    case ROGUE_KEY_SOUTH:
      if (allow_off_screen || (*row < (DROWS-2))) {
			(*row)++;
		}
		break;
	case ROGUE_KEY_NORTH:
		if (allow_off_screen || (*row > MIN_ROW)) {
			(*row)--;
		}
		break;
	case ROGUE_KEY_EAST:
		if (allow_off_screen || (*col < (DCOLS-1))) {
			(*col)++;
		}
		break;
	case ROGUE_KEY_NORTHWEST:
		if (allow_off_screen || ((*row > MIN_ROW) && (*col > 0))) {
			(*row)--;
			(*col)--;
		}
		break;
	case ROGUE_KEY_NORTHEAST:
		if (allow_off_screen || ((*row > MIN_ROW) && (*col < (DCOLS-1)))) {
			(*row)--;
			(*col)++;
		}
		break;
	case ROGUE_KEY_SOUTHEAST:
		if (allow_off_screen || ((*row < (DROWS-2)) && (*col < (DCOLS-1)))) {
			(*row)++;
			(*col)++;
		}
		break;
	case ROGUE_KEY_SOUTHWEST:
		if (allow_off_screen || ((*row < (DROWS-2)) && (*col > 0))) {
			(*row)++;
			(*col)--;
		}
		break;
	}
}
