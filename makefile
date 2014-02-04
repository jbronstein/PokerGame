game: game.c deal.c shuffle.c display.c exchange.c analyze.c initialize.c MC.c winner.c
		gcc -Wall -o game game.c deal.c shuffle.c display.c exchange.c analyze.c initialize.c MC.c winner.c

make clean:
		rm -f game

