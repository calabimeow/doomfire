all:
	gcc -Wall doomfire.c -o doomfire -I. -L. -lmallow
	./doomfire
