# LinuxRogue makefile
# by Ashwin N <ashwin@despammed.com> 

SHELL = /bin/bash
CC = gcc

# Define either of KEYS_QWERTY or KEYS_DVORAK below
CFLAGS = -DKEYS_QWERTY

LDFLAGS = -lncurses 

SOURCES = hit.c init.c level.c \
		  message.c move.c object.c play.c random.c \
		  room.c
OBJECTS = $(SOURCES:.c=.o)

all:		rogue

rogue: main.o $(OBJECTS)
	$(CC) main.o $(OBJECTS) $(LDFLAGS) -o rogue

include $(DFILES)

throw.o:	throw.c
		$(CC) $(CFLAGS) -c throw.c

zap.o:		zap.c
		$(CC) $(CFLAGS) -c zap.c

clean:
	rm -f $(OBJECTS) main.o rogue
