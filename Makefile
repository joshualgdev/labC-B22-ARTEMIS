CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
LDLIBS = -lm

.PHONY: all clean
all: artemis

artemis: main.c artemis.c validaciones.c artemis.h validaciones.h
	$(CC) $(CFLAGS) main.c artemis.c validaciones.c -o $@ $(LDLIBS)

clean:
	rm -f artemis
