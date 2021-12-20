#ifndef _KEYS_H_
#define _KEYS_H_

#define ROGUE_KEY_NORTH           'k'
#define ROGUE_KEY_SOUTH           'j'
#define ROGUE_KEY_EAST            'l'
#define ROGUE_KEY_WEST            'h'
#define ROGUE_KEY_NORTHEAST       'u'
#define ROGUE_KEY_NORTHWEST       'y'
#define ROGUE_KEY_SOUTHEAST       'n'
#define ROGUE_KEY_SOUTHWEST       'b'

#define ROGUE_KEY_NORTH_SHIFT     (ROGUE_KEY_NORTH+('A'-'a'))
#define ROGUE_KEY_SOUTH_SHIFT     (ROGUE_KEY_SOUTH+('A'-'a'))
#define ROGUE_KEY_EAST_SHIFT      (ROGUE_KEY_EAST+('A'-'a'))
#define ROGUE_KEY_WEST_SHIFT      (ROGUE_KEY_WEST+('A'-'a'))
#define ROGUE_KEY_NORTHEAST_SHIFT (ROGUE_KEY_NORTHEAST+('A'-'a'))
#define ROGUE_KEY_NORTHWEST_SHIFT (ROGUE_KEY_NORTHWEST+('A'-'a'))
#define ROGUE_KEY_SOUTHEAST_SHIFT (ROGUE_KEY_SOUTHEAST+('A'-'a'))
#define ROGUE_KEY_SOUTHWEST_SHIFT (ROGUE_KEY_SOUTHWEST+('A'-'a'))

#define ROGUE_KEY_NORTH_CTRL      (ROGUE_KEY_NORTH-('a'-1))
#define ROGUE_KEY_SOUTH_CTRL      (ROGUE_KEY_SOUTH-('a'-1))
#define ROGUE_KEY_EAST_CTRL       (ROGUE_KEY_EAST-('a'-1))
#define ROGUE_KEY_WEST_CTRL       (ROGUE_KEY_WEST-('a'-1))
#define ROGUE_KEY_NORTHEAST_CTRL  (ROGUE_KEY_NORTHEAST-('a'-1))
#define ROGUE_KEY_NORTHWEST_CTRL  (ROGUE_KEY_NORTHWEST-('a'-1))
#define ROGUE_KEY_SOUTHEAST_CTRL  (ROGUE_KEY_SOUTHEAST-('a'-1))
#define ROGUE_KEY_SOUTHWEST_CTRL  (ROGUE_KEY_SOUTHWEST-('a'-1))

#define ROGUE_KEY_DROP_CHECK      '>'
#define ROGUE_KEY_CHECK_UP        '<'

#define ROGUE_KEY_REMESSAGE       '\020'
#define ROGUE_KEY_VERSION         'v'
#define ROGUE_KEY_QUIT            'Q'
#define ROGUE_KEY_SAVE_GAME       'S'
#define ROGUE_KEY_WHATISIT        '/'
#define ROGUE_KEY_NOP             ' '

#define ROGUE_KEY_CANCEL          '\033'
#define ROGUE_KEY_LIST            '*'
#define ROGUE_KEY_SAVE_SCREEN     'X'
#define ROGUE_KEY_REFRESH         '\022'
#define ROGUE_KEY_FLUSH           '\032'


#define ROGUE_KEY_WIZARDIZE       '\027'
#define ROGUE_KEY_WIZ_INVENTORY   '\011'
#define ROGUE_KEY_WIZ_MAGIC_MAP   '\023'
#define ROGUE_KEY_WIZ_SHOW_TRAPS  '\024'
#define ROGUE_KEY_WIZ_SHOW_OBJS   '\017'
#define ROGUE_KEY_SHOW_AV_HP      '\001'
#define ROGUE_KEY_WIZ_NEW_OBJ     '\177'
#define ROGUE_KEY_WIZ_SHOW_MONST  '\015'

#endif	/* _KEYS_QWERTY_H_ */
