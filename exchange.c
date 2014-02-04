#include "poker_header.h"

/*Exchange ONLY for the User*/
void exchangeCards(Player * nPlayer, Deck * wDeck){
	char eCards[5];
	int i, numCards;
	printf("\nHow many cards would you like to exchange (0 to 5)? Please type a #: ");
	scanf("%d", &numCards);
	printf("Which cards would you like to exchange? (If none, then type a)\nJust put down the letters (no spaces!!!): ");
	scanf("%s", eCards);

/*Based on user input, exchange cards by letters user chose, then dequeue the card from the deck*/
	for (i = 0; i < numCards; i++){
		if (eCards[i] == 'a'){
			nPlayer[0].hand[0] = wDeck->stack[0];
			dequeue(wDeck);
		}			
		if (eCards[i] == 'b'){
			nPlayer[0].hand[1] = wDeck->stack[0];
			dequeue(wDeck); 
		}				
		if (eCards[i] == 'c'){
			nPlayer[0].hand[2] = wDeck->stack[0];
			dequeue(wDeck); 
		}
		if (eCards[i] == 'd'){
			nPlayer[0].hand[3] = wDeck->stack[0];
			dequeue(wDeck); 
		}
		if (eCards[i] == 'e'){
			nPlayer[0].hand[4] = wDeck->stack[0];
			dequeue(wDeck); 
		}
	}
}

/*exchange cards for three computers based on their Monte Carlo Advice*/
void computerExchange(Player * nPlayer, Deck * wDeck, int numPlayer){
int i;
	for (i = 0; i<5; i++){
		if (nPlayer[numPlayer].mcAdvice[i] == 1)
				nPlayer[numPlayer].hand[i] = wDeck->stack[0];
				dequeue(wDeck);
	}
}
