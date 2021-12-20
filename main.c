#include "rogue.h"
#include "init.h"
#include "level.h"
#include "message.h"
#include "object.h"
#include "play.h"

int main(void)
{
  init();
  for (;;) {
    clear_level();
    make_level();
    put_player(party_room);
    play_level();
  }
  return 0;
}
