#include "poker_header.h"

/*standard shuffle through permutations from 1-52*/
void shuffleDeck(Deck * wDeck){

	int i, j;
	Card temp;

	for (i = 0; i < DSIZE; i++){
		j = rand() % 52;
		temp = wDeck->stack[i];
		wDeck->stack[i] = wDeck->stack[j];
		wDeck->stack[j] = temp;
	}
}

/*Same idea as above, but only for the 47 cards in the Monte Carlo Simulation Deck*/
void shuffleDeckMC(Deck * wDeck){
	int i, j;
	Card temp;
	for (i = 0; i < 47; i++){
		j = rand() % 47;
		temp = wDeck->stack[i];
		wDeck->stack[i] = wDeck->stack[j];
		wDeck->stack[j] = temp;
	}
}

