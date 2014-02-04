#include "poker_header.h"

void fillDeck(Deck * wDeck){
/*Fill the deck with all 52 cards*/
	char *wFace[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
	char *wSuit[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

	int i;

	for (i=0; i < DSIZE; i++){
		wDeck->stack[i].face = wFace[i%13];
		wDeck->stack[i].suit = wSuit[i/13];
	}
}


void setup(Player * nPlayer, char * uName){
	/*SETUP the game for the user, add in the 3 computer players*/
	
	printf("\n\n\n=========================  Welcome to Wizard's Poker ===========================\n\n\n");

	sleep(1);

	printf("Welcome to Hogwarts, are you ready for some Wizard's Poker?\n\n");

	printf("To get started, what's your name? Type here: ");
	scanf("%s", uName);

	nPlayer[0].name = uName;
	nPlayer[0].galleons = 100;
	nPlayer[1].name = "Harry Potter";
	nPlayer[1].galleons = 100;
	nPlayer[2].name = "Professor Dumbledore";
	nPlayer[2].galleons = 100;
	nPlayer[3].name = "Lord Voldemort";
	nPlayer[3].galleons = 100;

	printf("\nWell %s, first thing is first, you will be playing against Harry Potter, Professor Dumbledore, and Lord Voldemort\n", uName);

	printf("\nYou will have 100 Galleons to start, but be aware, every hand you play costs 5 Galleons for all players. After you decide whether to play, you can exchange whichever cards you want and then either place a bet, match an opponent's bet, pass or fold. Also, to help you since you are new at wizarding poker, we decided to have The Sorting Hat provide advice on what to do. The Sorting Hat magically knows which cards to exchange in order to increase your Hand's value, so listen to him!\n");
}

