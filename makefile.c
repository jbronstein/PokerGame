game: game.c deal.c shuffle.c
		gcc -Wall -o game game.c deal.c shuffle.c

make clean:
		rm -f game
