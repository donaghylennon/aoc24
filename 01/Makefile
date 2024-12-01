CC=gcc
CFLAGS=-Wextra -Wall -pedantic -g -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code

main: main.c
	$(CC) $(CFLAGS) $^ -o $@
