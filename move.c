#include <ncurses.h>
#include <string.h>
#include "rogue.h"
#include "hit.h"
#include "keys.h"
#include "message.h"
#include "move.h"
#include "object.h"
#include "random.h"
#include "room.h"
#include "level.h"

boolean jump = 1;

int one_move_rogue(short dirch, short pickup)
{
	short row, col;
	char desc[DCOLS];
	short n, status;

	row = rogue.row;
	col = rogue.col;

	get_dir_rc(dirch, &row, &col, 1);

	if (!can_move(rogue.row, rogue.col, row, col))
	{
		return(MOVE_FAILED);
	}
	if (dungeon[row][col] & DOOR) {
		if (cur_room == PASSAGE)
		{
			cur_room = get_room_number(row, col);
			light_up_room(cur_room);
		}
		else
		{
			light_passage(row, col);
		}
	} else if ((dungeon[rogue.row][rogue.col] & DOOR)
	           && (dungeon[row][col] & TUNNEL)) {
		light_passage(row, col);
		darken_room(cur_room);
		cur_room = PASSAGE;
	} else if (dungeon[row][col] & TUNNEL) {
			light_passage(row, col);
	}
	mvaddch(rogue.row, rogue.col, get_dungeon_char(rogue.row, rogue.col));
	mvaddch(row, col, rogue.fchar);

	if (!jump)
	{
		refresh();
	}
	rogue.row = row;
	rogue.col = col;
	if (dungeon[row][col] & (DOOR/* | STAIRS | TRAP*/))
	{
		return(STOPPED_ON_SOMETHING);
	}
	return MOVED;
}

int is_passable(int row, int col)
{
	if ((row < MIN_ROW) || (row > (DROWS - 2)) || (col < 0)
	    || (col > (DCOLS-1)))
	{
		return(0);
	}
	if (dungeon[row][col] & HIDDEN)
	{
		return((dungeon[row][col]) ? 1 : 0);
	}
	return(dungeon[row][col] & (FLOOR | TUNNEL | DOOR));
}

int can_move(int row1, int col1, int row2, int col2)
{
	if (!is_passable(row2, col2))
	{
		return(0);
	}
	if ((row1 != row2) && (col1 != col2))
	{
		if ((dungeon[row1][col1]&DOOR)||(dungeon[row2][col2]&DOOR))
		{
			return(0);
		}
		if ((!dungeon[row1][col2]) || (!dungeon[row2][col1]))
		{
			return(0);
		}
	}
	return(1);
}
