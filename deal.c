#include "poker_header.h"

/*For dealing, I pass each player the top card and dequeue that card*/
void dealOut(Deck * wDeck, Player * totalPlayers){
	int i, j, num;
	j = num = 0;
	for (i = 0; i < 5; i++){	
		for (j = 0; j<4; j++){
			totalPlayers[j].hand[num] = wDeck->stack[0];
			dequeue(wDeck);
		}
		num++;
	}
}


/*For dequeue, I just overwrite the top card stack[0], and shift all cards up one*/
void dequeue(Deck * wDeck){
	int i, j;
	j = 0;
	for (i = 1; i<52; i++){
		wDeck->stack[j] = wDeck->stack[i]; 
		j++;
	}
}
